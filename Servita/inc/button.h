/**
 * @file button.h
 * @brief Button handling for drink pouring.
 * @version 0.1
 * @date 2024-05-31
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define CANCEL_HOLD_TIME 3000  // 3 seconds
#define TRIGGER_HOLD_TIME 100  // 100ms

enum Buttons {
    BUTTON1,
    BUTTON2
};

// Function declarations
bool is_button_pressed(Buttons button);
void init_buttons();
void IRAM_ATTR handle_button1();
void IRAM_ATTR handle_button2();
void pour_trigger_check();
void pour_cancel_check();
void button_loop();

#endif // BUTTON_H
