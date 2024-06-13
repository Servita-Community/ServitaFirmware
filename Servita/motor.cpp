/**
 * @file motor.cpp
 * @brief Pump pins, functions, and variables.
 * @version 0.1
 * @date 2024-05-28
 */
#include <ArduinoJson.h>
#include "inc/motor.h"
#include "inc/led.h"

motor_t pump1 = {PUMP1_HIGH_PIN, PUMP1_LOW_PIN, PUMP1_ENABLE_PIN, MOTOR_OFF, PUMP1};
motor_t pump2 = {PUMP2_HIGH_PIN, PUMP2_LOW_PIN, PUMP2_ENABLE_PIN, MOTOR_OFF, PUMP2};
motor_t gantry = {GANTRY_UP_PIN, GANTRY_DOWN_PIN, GANTRY_ENABLE_PIN, MOTOR_OFF, GANTRY};
bool hardware_error = false;

void init_limit_switches() {
    pinMode(LIMIT_SWITCH_TOP, INPUT_PULLDOWN);
    pinMode(LIMIT_SWITCH_BOTTOM, INPUT_PULLDOWN);

    attachInterrupt(LIMIT_SWITCH_TOP, disable_motor_isr, FALLING);
    attachInterrupt(LIMIT_SWITCH_BOTTOM, disable_motor_isr, FALLING);
}

void init_motor(motor_t *motor) {
    pinMode(motor->high_pin, OUTPUT);
    pinMode(motor->low_pin, OUTPUT);
    pinMode(motor->enable_pin, OUTPUT);

    digitalWrite(motor->high_pin, LOW);
    digitalWrite(motor->low_pin, LOW);
    digitalWrite(motor->enable_pin, LOW);
}

void init_motors() {
    init_motor(&pump1);
    init_motor(&pump2);
    init_motor(&gantry);

    bool top_limit_triggered = digitalRead(LIMIT_SWITCH_TOP) == LOW;
    bool bottom_limit_triggered = digitalRead(LIMIT_SWITCH_BOTTOM) == LOW;

    delay(LIMIT_SWITCH_SETTLE_TIME);

    if (top_limit_triggered && bottom_limit_triggered) {
        hardware_error = true;
        set_board_led(LIMIT_SWITCH_ERROR_COLOR);
        Serial.println(
            "Limit switches not attached or gantry high/low and other switch isn't attached."
        );
    } else if (top_limit_triggered || bottom_limit_triggered) {
        set_motor_state(&gantry, top_limit_triggered ? MOTOR_DOWN : MOTOR_UP);
        uint32_t start_time = millis();
        while (digitalRead(top_limit_triggered ? LIMIT_SWITCH_TOP : LIMIT_SWITCH_BOTTOM) == LOW) {
            if (millis() - start_time > GANTRY_END_CHECK_TIME) {
                hardware_error = true;
                set_board_led(LIMIT_SWITCH_ERROR_COLOR);
                Serial.printf(
                    "The %s limit switch appears to not be attached.", 
                    top_limit_triggered ? "top" : "bottom"
                );
                set_motor_state(&gantry, MOTOR_OFF);
                return;
            }
        }
        uint32_t dt = millis() - start_time;
        delay(LIMIT_SWITCH_SETTLE_TIME);

        set_motor_state(&gantry, MOTOR_UP);
        Serial.printf("Gantry was initially at the %s limit switch, both switches active\n", 
            top_limit_triggered ? "top" : "bottom"
        );
        Serial.printf("Limit switch check took %u ms.\n", dt);
    } else {
        Serial.println("Both limit switches are active, gantry is not at the top or bottom.");
        set_motor_state(&gantry, MOTOR_UP);
    }
}

bool set_motor_state(motor_t *motor, motor_state_t state) {
    if (motor->state == state)      return false;

    switch (state) {
        case MOTOR_OFF:
            digitalWrite(motor->high_pin, LOW);
            digitalWrite(motor->low_pin, LOW);
            digitalWrite(motor->enable_pin, HIGH);
            break;
        case MOTOR_ON:
            if (motor->type == GANTRY)                          return false;
            digitalWrite(motor->high_pin, HIGH);
            digitalWrite(motor->low_pin, LOW);
            digitalWrite(motor->enable_pin, HIGH);
            break;
        case MOTOR_UP:
            if (motor->type != GANTRY)                          return false;
            if (hardware_error)                                 return false;
            if (digitalRead(LIMIT_SWITCH_TOP) == LOW)           return false;

            digitalWrite(motor->high_pin, HIGH);
            digitalWrite(motor->low_pin, LOW);
            digitalWrite(motor->enable_pin, HIGH);
            break;
        case MOTOR_DOWN:
            if (motor->type != GANTRY)                          return false;
            if (hardware_error)                                 return false;
            if (digitalRead(LIMIT_SWITCH_BOTTOM) == LOW)        return false;

            digitalWrite(motor->high_pin, LOW);
            digitalWrite(motor->low_pin, HIGH);
            digitalWrite(motor->enable_pin, HIGH);
            break;
    }
    motor->state = state;
    return true;
}

void IRAM_ATTR disable_motor_isr() {
    set_motor_state(&gantry, MOTOR_OFF);
}

void handle_motor_json(JsonObject payload) {
    const char *action = payload["action"];
    if (strcmp(action, "mCarUp") == 0) {
        set_motor_state(&gantry, MOTOR_UP);
    } else if (strcmp(action, "mCarDown") == 0) {
        set_motor_state(&gantry, MOTOR_DOWN);
    } else if (strcmp(action, "mCarStop") == 0) {
        set_motor_state(&gantry, MOTOR_OFF);
    } else if (strcmp(action, "rPump1Start") == 0) {
        set_motor_state(&pump1, MOTOR_ON);
    } else if (strcmp(action, "rPump1Stop") == 0) {
        set_motor_state(&pump1, MOTOR_OFF);
    } else if (strcmp(action, "rPump2Start") == 0) {
        set_motor_state(&pump2, MOTOR_ON);
    } else if (strcmp(action, "rPump2Stop") == 0) {
        set_motor_state(&pump2, MOTOR_OFF);
    } else if (strcmp(action, "mCarHome") == 0) {
        set_motor_state(&gantry, MOTOR_UP);
    }
}