/**
 * @file button.cpp
 * @brief Button handling for drink pouring.
 * @version 0.1
 * @date 2024-05-30
 */

#include "inc/button.h"
#include "inc/pour.h"
#include "inc/motor.h"

volatile bool button1_pressed = false;
volatile bool button2_pressed = false;

void init_buttons() {
    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), handle_button1, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), handle_button2, FALLING);
}

void IRAM_ATTR handle_button1() {
    button1_pressed = true;
}

void IRAM_ATTR handle_button2() {
    button2_pressed = true;
}

void button_loop() {
    if (button1_pressed) {
        button1_pressed = false;
        if (drink_pour.state == IDLE) {
            start_pour(DRINK1);
        } else if (drink_pour.state == GANTRY_DECENDING && drink_pour.drink == DRINK2) {
            drink_pour.drink = MIXED;
        }
    }

    if (button2_pressed) {
        button2_pressed = false;
        if (drink_pour.state == IDLE) {
            start_pour(DRINK2);
        } else if (drink_pour.state == GANTRY_DECENDING && drink_pour.drink == DRINK1) {
            drink_pour.drink = MIXED;
        }
    }
}