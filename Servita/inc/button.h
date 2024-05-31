/**
 * @file button.h
 * @brief Button handling for drink pouring.
 * @version 0.1
 * @date 2024-05-31
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define BUTTON1_PIN 32
#define BUTTON2_PIN 27

// Function declarations
void init_buttons();
void IRAM_ATTR handle_button1();
void IRAM_ATTR handle_button2();
void button_loop();

#endif // BUTTON_H
