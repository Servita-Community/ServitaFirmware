/**
 * @file serial_cmd.h
 * @brief Serial command handling for drink pouring.
 * @version 0.1
 * @date 2024-05-31
 */

#ifndef SERIAL_CMD_H
#define SERIAL_CMD_H

#include <Arduino.h>

// Define command struct
typedef struct {
    const char *command;
    void (*function)();
} serial_command_t;

// Function declarations
void init_serial_commands();
void process_serial_command();

#endif // SERIAL_CMD_H
