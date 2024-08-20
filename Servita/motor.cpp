/**
 * @file motor.cpp
 * @brief Pump pins, functions, and variables.
 * @version 0.1
 * @date 2024-05-28
 */
#include <ArduinoJson.h>
#include "inc/motor.h"
#include "inc/led.h"
#include "inc/pour.h"
#include "inc/pins.h"
#include "inc/expansion.h"

motor_t pump1 = {&PUMP1_HIGH_PIN, &PUMP1_LOW_PIN, &PUMP1_ENABLE_PIN, MOTOR_OFF, PUMP1};
motor_t pump2 = {&PUMP2_HIGH_PIN, &PUMP2_LOW_PIN, &PUMP2_ENABLE_PIN, MOTOR_OFF, PUMP2};
motor_t gantry = {&GANTRY_UP_PIN, &GANTRY_DOWN_PIN, &GANTRY_ENABLE_PIN, MOTOR_OFF, GANTRY};
gantry_state_t gantry_state = GANTRY_NONE;
uint32_t last_motor_start_time = 0;

void init_limit_switches() {
    pinMode(LIMIT_SWITCH_TOP, INPUT);
    pinMode(LIMIT_SWITCH_BOTTOM, INPUT);

    attachInterrupt(LIMIT_SWITCH_TOP, disable_motor_isr, FALLING);
    attachInterrupt(LIMIT_SWITCH_BOTTOM, disable_motor_isr, FALLING);
}

void init_motor(motor_t *motor) {
    pinMode(*(motor->high_pin), OUTPUT);
    pinMode(*(motor->low_pin), OUTPUT);
    pinMode(*(motor->enable_pin), OUTPUT);

    digitalWrite(*(motor->high_pin), LOW);
    digitalWrite(*(motor->low_pin), LOW);
    digitalWrite(*(motor->enable_pin), LOW);
}

void manual_gantry_control(motor_state_t state) {
    if (state == MOTOR_ON) {
        Serial.println("Invalid manual gantry control state requested");                    return;
    }

    switch (gantry_state) {
        case GANTRY_HOMING:
            Serial.println("Homing canceled for manual movement.");                         break;
        case GANTRY_POURING:
            Serial.println("Cannot manually control gantry while pouring.");                return;
        case GANTRY_MANUAL_UP:
            if (state == MOTOR_UP) {
                Serial.println("Manual move of gantry up already triggered");               return;
            } else if (state == MOTOR_DOWN) {
                Serial.println("Manual move of gantry up canceled for manual down.");       break;
            } else {
                Serial.println("Manual move of gantry up stopped by manual stop.");         break;
            }
        case GANTRY_MANUAL_DOWN:
            if (state == MOTOR_DOWN) {
                Serial.println("Manual move of gantry down already triggered");             return;
            } else if (state == MOTOR_UP) {
                Serial.println("Manual move of gantry down canceled for manual up.");       break;
            } else {
                Serial.println("Manual move of gantry down stopped by manual stop.");       break;
            }
        default:
            break;
    }

    switch (state) {
        case MOTOR_UP:
            Serial.println("Manual move of gantry up triggered.");      break;
        case MOTOR_DOWN:
            Serial.println("Manual move of gantry down triggered.");    break;
        case MOTOR_OFF:
            Serial.println("Manual stop of gantry triggered.");         break;
    }
    gantry_state = state == MOTOR_UP ? GANTRY_MANUAL_UP : state == MOTOR_DOWN ? GANTRY_MANUAL_DOWN : GANTRY_NONE;
    set_motor_state(&gantry, state);
}

void home_gantry() {
    switch (gantry_state) {
        case GANTRY_HOMING:
            Serial.println("Gantry already homing.");                               return;
        case GANTRY_POURING:
            Serial.println("Cannot home gantry while pouring.");                    return;
        case GANTRY_MANUAL_UP:
            Serial.println("Manual move of gantry up canceled for homing.");        break;
        case GANTRY_MANUAL_DOWN:
            Serial.println("Manual move of gantry down canceled for homing.");      break;
        default:
            break;
    }

    set_motor_state(&gantry, MOTOR_UP);
    delay(LIMIT_SWITCH_DEBOUNCE);
    set_motor_state(&gantry, MOTOR_UP);
    gantry_state = GANTRY_HOMING;
}

void init_motors() {
    init_motor(&pump1);
    if (expansion_type == DUO_BOARD)        init_motor(&pump2);
    init_motor(&gantry);
    home_gantry();
}

bool set_motor_state(motor_t *motor, motor_state_t state) {
    if (motor->type == PUMP2 && expansion_type != DUO_BOARD)      return false;
    if (motor->state == state)      return false;

    switch (state) {
        case MOTOR_OFF:
            digitalWrite(*(motor->high_pin), LOW);
            digitalWrite(*(motor->low_pin), LOW);
            digitalWrite(*(motor->enable_pin), HIGH);
            break;
        case MOTOR_ON:
            if (motor->type == GANTRY)                          return false;
            digitalWrite(*(motor->high_pin), HIGH);
            digitalWrite(*(motor->low_pin), LOW);
            digitalWrite(*(motor->enable_pin), HIGH);
            break;
        case MOTOR_UP:
            if (motor->type != GANTRY)                          return false;
            if (digitalRead(LIMIT_SWITCH_TOP) == LOW)           return false;

            digitalWrite(*(motor->high_pin), HIGH);
            digitalWrite(*(motor->low_pin), LOW);
            digitalWrite(*(motor->enable_pin), HIGH);
            last_motor_start_time = millis();
            break;
        case MOTOR_DOWN:
            if (motor->type != GANTRY)                          return false;
            if (digitalRead(LIMIT_SWITCH_BOTTOM) == LOW)        return false;

            digitalWrite(*(motor->high_pin), LOW);
            digitalWrite(*(motor->low_pin), HIGH);
            digitalWrite(*(motor->enable_pin), HIGH);
            last_motor_start_time = millis();
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
        manual_gantry_control(MOTOR_UP);
    } else if (strcmp(action, "mCarDown") == 0) {
        manual_gantry_control(MOTOR_DOWN);
    } else if (strcmp(action, "mCarStop") == 0) {
        manual_gantry_control(MOTOR_OFF);
    } else if (strcmp(action, "rPump1Start") == 0) {
        set_motor_state(&pump1, MOTOR_ON);
    } else if (strcmp(action, "rPump1Stop") == 0) {
        set_motor_state(&pump1, MOTOR_OFF);
    } else if (strcmp(action, "rPump2Start") == 0) {
        set_motor_state(&pump2, MOTOR_ON);
    } else if (strcmp(action, "rPump2Stop") == 0) {
        set_motor_state(&pump2, MOTOR_OFF);
    } else if (strcmp(action, "mCarHome") == 0) {
        home_gantry();
    }
}

void motor_loop() {
    switch (gantry_state) {
        case GANTRY_HOMING:
            if (digitalRead(LIMIT_SWITCH_TOP) != LOW) {
                set_motor_state(&gantry, MOTOR_UP);
            } else {
                set_motor_state(&gantry, MOTOR_OFF);
                gantry_state = GANTRY_NONE;
                Serial.println("Gantry homing complete.");
            }
            break;
        case GANTRY_MANUAL_UP:
            if (digitalRead(LIMIT_SWITCH_TOP) != LOW) {
                set_motor_state(&gantry, MOTOR_UP);
            } else {
                set_motor_state(&gantry, MOTOR_OFF);
                gantry_state = GANTRY_NONE;
                Serial.println("Manual move of gantry up complete.");
            }
            break;
        case GANTRY_MANUAL_DOWN:
            if (digitalRead(LIMIT_SWITCH_BOTTOM) != LOW) {
                set_motor_state(&gantry, MOTOR_DOWN);
            } else {
                set_motor_state(&gantry, MOTOR_OFF);
                gantry_state = GANTRY_NONE;
                Serial.println("Manual move of gantry down complete.");
            }
            break;
        default:
            break;
    }

    if (gantry.state != MOTOR_OFF && (millis() - last_motor_start_time) > GANTRY_TIMEOUT) {
        set_motor_state(&gantry, gantry.state == MOTOR_UP ? MOTOR_DOWN : MOTOR_UP);
        delay(MOTOR_BACKOFF_TIME);
        set_motor_state(&gantry, MOTOR_OFF);
        set_board_color(RGB::LOCKOUT_COLOR);
        lockout = true;
        Serial.println("Gantry timeout...");
        if (drink_pour.state != IDLE)               abort_pour();
    }
}