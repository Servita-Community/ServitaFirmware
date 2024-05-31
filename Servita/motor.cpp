/**
 * @file motor.cpp
 * @brief Pump pins, functions, and variables.
 * @version 0.1
 * @date 2024-05-28
 */
#include "inc/motor.h"

motor_t pump1 = {PUMP1_HIGH_PIN, PUMP1_LOW_PIN, PUMP1_ENABLE_PIN, MOTOR_OFF, PUMP1};
motor_t pump2 = {PUMP2_HIGH_PIN, PUMP2_LOW_PIN, PUMP2_ENABLE_PIN, MOTOR_OFF, PUMP2};
motor_t gantry = {GANTRY_UP_PIN, GANTRY_DOWN_PIN, GANTRY_ENABLE_PIN, MOTOR_OFF, GANTRY};

void init_limit_switches() {
    pinMode(LIMIT_SWITCH_TOP, INPUT);
    pinMode(LIMIT_SWITCH_BOTTOM, INPUT);

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

    if (digitalRead(LIMIT_SWITCH_TOP) == HIGH)      set_motor_state(&gantry, MOTOR_UP);
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
            if (digitalRead(LIMIT_SWITCH_TOP) == LOW)           return false;

            digitalWrite(motor->high_pin, HIGH);
            digitalWrite(motor->low_pin, LOW);
            digitalWrite(motor->enable_pin, HIGH);
            break;
        case MOTOR_DOWN:
            if (motor->type != GANTRY)                          return false;
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