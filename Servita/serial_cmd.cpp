/**
 * @file serial_cmd.cpp
 * @brief Serial command handling for drink pouring.
 * @version 0.1
 * @date 2024-05-31
 */

#include "inc/serial_cmd.h"
#include "inc/motor.h"
#include "inc/pour.h"
#include "inc/server.h"
#include "inc/version.h"
#include "inc/led.h"
#include "inc/expansion.h"

// Define commands
serial_command_t serial_commands[] = {
    {"drink1", [](String params){ start_pour(DRINK1); }},
    {"printPourSizes", [](String params){
        Serial.printf("Drink 1: %u ms\n", drink1_pour_size);
    }},
    {"down", [](String params){ manual_gantry_control(MOTOR_DOWN); }},
    {"up", [](String params){ manual_gantry_control(MOTOR_UP); }},
    {"stop", [](String params){ manual_gantry_control(MOTOR_OFF); }},
    {"cancel", [](String params){ abort_pour(); }},
    {"restart", [](String params){ ESP.restart(); }},
    {"deleteCredentials", [](String params){ delete_credentials(); }},
    {"getBrdVersion", [](String params){ get_board_version(); }},
    {"saveBrdVersion", handle_save_brd_version},
    {"getExpansionType", [](String params){get_expansion_version(); }},
    {"saveExpansionType", handle_save_expansion_type},
    {"setBoardLed", handle_set_board_led},
    {"setMinTofDistance", [](String params){ 
        // Check if the new min distance is less than the max distance and is an integer
        if (params.toInt() > 0) {
            min_distance = params.toInt();
            mid_distance = (min_distance + max_distance) / 2;
        } else {
            Serial.println("Invalid min distance.");
        }
    }},
    {"setMaxTofDistance", [](String params){
        // Check if the new max distance is greater than the min distance and is an integer
        if (params.toInt() > 0) {
            max_distance = params.toInt();
            mid_distance = (min_distance + max_distance) / 2;
        } else {
            Serial.println("Invalid max distance.");
        }
    }},
    {"setTofTimeoutMs", [](String params){
        // Check if the new timeout is greater than 0 and is an integer
        if (params.toInt() > 0) {
            drawer_timeout_ms = params.toInt();
        } else {
            Serial.println("Invalid timeout.");
        }
    }},
    {"getMinTofDistance", [](String params){ Serial.printf("Min TOF Distance: %d\n", min_distance);}},
    {"getMaxTofDistance", [](String params){ Serial.printf("Max TOF Distance: %d\n", max_distance);}},
    {"getTofTimeoutMs", [](String params){ Serial.printf("TOF Timeout ms: %d\n", drawer_timeout_ms);}},
    {"version", [](String params){ Serial.printf("Software version: %s\n", SOFTWARE_VERSION); }}
};

// Number of commands
const size_t num_serial_commands = sizeof(serial_commands) / sizeof(serial_command_t);

void init_serial_commands() {
    if (!Serial) {
        Serial.begin(115200); // Initialize serial communication
    }
}

void process_serial_command() {
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        command.trim(); // Remove any leading/trailing whitespace

        int firstSpaceIndex = command.indexOf(' ');
        String cmd;
        String params;

        if (firstSpaceIndex != -1) {
            cmd = command.substring(0, firstSpaceIndex);
            params = command.substring(firstSpaceIndex + 1);
        } else {
            cmd = command;
            params = "";
        }

        for (size_t i = 0; i < num_serial_commands; ++i) {
            if (cmd.equalsIgnoreCase(serial_commands[i].command)) {
                serial_commands[i].function(params);
                return;
            }
        }
        Serial.println("Unknown command.");
    }
}