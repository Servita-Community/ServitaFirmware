/**
 * @file motor.cpp
 * @author Tyler Bair (tyler.bair@protonmail.com)
 * @brief Pump pins, functions, and variables.
 * @version 0.1
 * @date 2024-05-28
 * 
 */
#include "inc/motor.h"

motor_t pump1 = {PUMP1_HIGH_PIN, PUMP1_LOW_PIN, PUMP1_ENABLE_PIN, MOTOR_OFF, PUMP1};
motor_t pump2 = {PUMP2_HIGH_PIN, PUMP2_LOW_PIN, PUMP2_ENABLE_PIN, MOTOR_OFF, PUMP2};
motor_t gantry = {GANTRY_UP_PIN, GANTRY_DOWN_PIN, GANTRY_ENABLE_PIN, MOTOR_OFF, GANTRY};

void init_motor(motor_t *motor) {
    pinMode(motor->high_pin, OUTPUT);
    pinMode(motor->low_pin, OUTPUT);
    pinMode(motor->enable_pin, OUTPUT);
    digitalWrite(motor->high_pin, LOW);
    digitalWrite(motor->low_pin, LOW);
    digitalWrite(motor->enable_pin, LOW);
    motor->state = MOTOR_OFF;
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
            if (motor->type == GANTRY)          return false;
            digitalWrite(motor->high_pin, HIGH);
            digitalWrite(motor->low_pin, LOW);
            digitalWrite(motor->enable_pin, HIGH);
            break;
        case MOTOR_UP:
            if (motor->type != GANTRY)          return false;
            digitalWrite(motor->high_pin, HIGH);
            digitalWrite(motor->low_pin, LOW);
            digitalWrite(motor->enable_pin, HIGH);
            break;
        case MOTOR_DOWN:
            if (motor->type != GANTRY)          return false;
            digitalWrite(motor->high_pin, LOW);
            digitalWrite(motor->low_pin, HIGH);
            digitalWrite(motor->enable_pin, HIGH);
            break;
    }
    motor->state = state;
    Serial.printf(
        "Motor state set to: %s for motor type: %s\n",
        MOTOR_STATE_TO_STRING(state),
        MOTOR_TYPE_TO_STRING(motor->type)
    );
    return true;
}