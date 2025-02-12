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
    {"drink2", [](String params){ start_pour(DRINK2); }},
    {"drink3", [](String params){ start_pour(MIXED); }},
    {"printPourSizes", [](String params){
        Serial.printf("Drink 1: %u ms\n", drink1_pour_size);
        if (expansion_type == DUO_BOARD) {
            Serial.printf("Drink 2: %u ms\n", drink2_pour_size);
            Serial.printf("Mixed 1: %u ms\n", mixed1_pour_size);
            Serial.printf("Mixed 2: %u ms\n", mixed2_pour_size);
        }
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
    {"version", [](String params){ Serial.printf("Software version: %s\n", SOFTWARE_VERSION); }},
    {"unfryLedArray" [](String parms){
        led_preferences.begin("led", false);
        led_preferences.putString("ledcheck", "");
        led_preferences.end();
        ESP.restart();
    }
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