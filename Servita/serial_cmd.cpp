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

// Define commands
serial_command_t serial_commands[] = {
    {"drink1", [](){ start_pour(DRINK1); }},
    {"drink2", [](){ start_pour(DRINK2); }},
    {"drink3", [](){ start_pour(MIXED); }},
    {"printPourSizes", [](){
        Serial.printf("Drink 1: %u ms\n", drink1_pour_size);
        Serial.printf("Drink 2: %u ms\n", drink2_pour_size);
        Serial.printf("Mixed 1: %u ms\n", mixed1_pour_size);
        Serial.printf("Mixed 2: %u ms\n", mixed2_pour_size);
    }},
    {"down", [](){ set_motor_state(&gantry, MOTOR_DOWN); }},
    {"up", [](){ set_motor_state(&gantry, MOTOR_UP); }},
    {"stop", [](){ set_motor_state(&gantry, MOTOR_OFF); }},
    {"cancel", abort_pour},
    {"restart", [](){ ESP.restart(); }},
    {"deleteCredentials", delete_credentials},
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

        for (size_t i = 0; i < num_serial_commands; ++i) {
            if (command.startsWith(serial_commands[i].command)) {
                serial_commands[i].function();
                return;
            }
        }
        Serial.println("Unknown command.");
    }
}
