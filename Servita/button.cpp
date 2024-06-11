/**
 * @file button.cpp
 * @brief Button handling for drink pouring.
 * @version 0.1
 * @date 2024-05-30
 */

#include "inc/button.h"
#include "inc/pour.h"
#include "inc/motor.h"
#include "inc/led.h"

volatile bool button1_pressed = false;
volatile bool button2_pressed = false;

unsigned long button1_press_time = 0;
unsigned long button2_press_time = 0;

bool is_button_pressed(Buttons button) {
    return digitalRead(button == BUTTON1 ? BUTTON1_PIN : BUTTON2_PIN) == LOW;
}

void init_buttons() {
    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), handle_button1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), handle_button2, CHANGE);
}

void IRAM_ATTR handle_button1() {
    button1_pressed = (digitalRead(BUTTON1_PIN) == LOW);
    button1_press_time = millis();
}

void IRAM_ATTR handle_button2() {
    button2_pressed = (digitalRead(BUTTON2_PIN) == LOW);
    button2_press_time = millis();
}

void pour_trigger_check() {
    bool b1_triggerable = (millis() - button1_press_time) > TRIGGER_HOLD_TIME && button1_pressed;
    bool b2_triggerable = (millis() - button2_press_time) > TRIGGER_HOLD_TIME && button2_pressed;

    if (drink_pour.state == IDLE) {
        if (b1_triggerable) {
            Serial.printf(
                "Starting pour from button1 time: %d ms\n", millis() - button1_press_time
            );
            start_pour(DRINK1);
            button1_press_time = millis();
        } else if (b2_triggerable) {
            Serial.printf(
                "Starting pour from button2 time: %d ms\n", millis() - button2_press_time
            );
            start_pour(DRINK2);
            button2_press_time = millis();
        }
    } else if (drink_pour.state == GANTRY_DECENDING) {
        if (b1_triggerable && drink_pour.drink == DRINK2) {
            Serial.printf(
                "Switching to mixed drink from button1 time: %d ms\n",
                millis() - button1_press_time
            );
            drink_pour.drink = MIXED;
            set_board_led(POUR_DRINK_MIXED_COLOR);
            button1_press_time = millis();
        } else if (b2_triggerable && drink_pour.drink == DRINK1) {
            Serial.printf(
                "Switching to mixed drink from button2 time: %d ms\n",
                millis() - button2_press_time
            );
            drink_pour.drink = MIXED;
            set_board_led(POUR_DRINK_MIXED_COLOR);
            button2_press_time = millis();
        }
    }
}

void pour_cancel_check() {
    bool b1_cancelable = (millis() - button1_press_time) > CANCEL_HOLD_TIME && button1_pressed;
    bool b2_cancelable = (millis() - button2_press_time) > CANCEL_HOLD_TIME && button2_pressed;

    if (drink_pour.state == GANTRY_DECENDING || drink_pour.state == POURING) {
        if (b1_cancelable) {
            Serial.printf("Pour cancelled by button1 time: %d ms\n", millis() - button1_press_time);
            button1_pressed = false;
            abort_pour();
        } else if (b2_cancelable) {
            Serial.printf("Pour cancelled by button2 time: %d ms\n", millis() - button2_press_time);
            button2_pressed = false;
            abort_pour();
        }
    }

}

void button_loop() {
    pour_trigger_check();
    pour_cancel_check();
}