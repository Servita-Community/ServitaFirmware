/**
 * @file pour.cpp
 * @author Tyler Bair (tyler.bair@protonmail.com)
 * @brief Pour size management, sequencing, and control.
 * @version 0.1
 * @date 2024-05-28
*/
#include "inc/pour.h"
#include "inc/motor.h"
#include <Preferences.h>

uint16_t drink1_pour_size;
uint16_t drink2_pour_size;
uint16_t mixed1_pour_size;
uint16_t mixed2_pour_size;
drink_pour_t drink_pour;

Preferences pour_preferences;

void init_pour_system() {
    pour_preferences.begin("pour", false);
    drink1_pour_size = pour_preferences.getUInt("drink1_pour_size", 0);
    drink2_pour_size = pour_preferences.getUInt("drink2_pour_size", 0);
    mixed1_pour_size = pour_preferences.getUInt("mixed1_pour_size", 0);
    mixed2_pour_size = pour_preferences.getUInt("mixed2_pour_size", 0);
    pour_preferences.end();

    drink_pour.drink = DRINK1;
    drink_pour.state = IDLE;
    drink_pour.pour_start_time = 0;
}

void set_pour_size(pour_size_setting_t setting, uint16_t pour_size) {
    pour_preferences.begin("pour", false);
    switch (setting) {
        case DRINK1_POUR_SIZE:
            drink1_pour_size = pour_size;
            pour_preferences.putUInt("drink1_pour_size", drink1_pour_size);
            break;
        case DRINK2_POUR_SIZE:
            drink2_pour_size = pour_size;
            pour_preferences.putUInt("drink2_pour_size", drink2_pour_size);
            break;
        case MIXED_POUR_1_SIZE:
            mixed1_pour_size = pour_size;
            pour_preferences.putUInt("mixed1_pour_size", mixed1_pour_size);
            break;
        case MIXED_POUR_2_SIZE:
            mixed2_pour_size = pour_size;
            pour_preferences.putUInt("mixed2_pour_size", mixed2_pour_size);
            break;
    }
    pour_preferences.end();
}

void start_pour(drink_t drink) {
    if (drink_pour.state != IDLE) {
        Serial.println("Pour already in progress.");
        return;
    }

    drink_pour.drink = drink;
    set_motor_state(&gantry, MOTOR_DOWN);
    drink_pour.state = GANTRY_DECENDING;
    Serial.printf("Starting pour for drink: %d\n", drink);
}

void pour_seq_loop() {
    switch (drink_pour.state) {
        case GANTRY_DECENDING:
            if (digitalRead(LIMIT_SWITCH_BOTTOM) == LOW) {
                drink_pour.pour_start_time = (uint64_t) millis();
                if (drink_pour.drink != DRINK2)             set_motor_state(&pump1, MOTOR_ON);
                if (drink_pour.drink != DRINK1)             set_motor_state(&pump2, MOTOR_ON);
                drink_pour.state = POURING;
                Serial.println("Gantry down all done switching to pouring.");
            } else {
                set_motor_state(&gantry, MOTOR_DOWN);
            }
            break;
        case POURING: {
            uint64_t pour_time = (uint64_t) millis() - drink_pour.pour_start_time;
            switch (drink_pour.drink) {
                case DRINK1:
                    if (pour_time >= drink1_pour_size) {
                        set_motor_state(&pump1, MOTOR_OFF);
                        set_motor_state(&gantry, MOTOR_UP);
                        drink_pour.state = GANTRY_ASCENDING;
                        Serial.println("Pouring complete switching to gantry up.");
                    }
                    break;
                case DRINK2:
                    if (pour_time >= drink2_pour_size) {
                        set_motor_state(&pump2, MOTOR_OFF);
                        set_motor_state(&gantry, MOTOR_UP);
                        drink_pour.state = GANTRY_ASCENDING;
                        Serial.println("Pouring complete switching to gantry up.");
                    }
                    break;
                case MIXED:
                    bool pump1_done = pour_time >= mixed1_pour_size;
                    bool pump2_done = pour_time >= mixed2_pour_size;

                    if (pump1_done)     set_motor_state(&pump1, MOTOR_OFF);
                    if (pump2_done)     set_motor_state(&pump2, MOTOR_OFF);

                    if (pump1_done && pump2_done) {
                        set_motor_state(&gantry, MOTOR_UP);
                        drink_pour.state = GANTRY_ASCENDING;
                        Serial.println("Pouring complete switching to gantry up.");
                    }
                    break;
            }
            break;
        }
        case GANTRY_ASCENDING:
            if (digitalRead(LIMIT_SWITCH_TOP) == LOW) {
                drink_pour.state = IDLE;
                Serial.println("Gantry up all done switching to idle.");
            } else {
                set_motor_state(&gantry, MOTOR_UP);
            }
            break;
        case IDLE:
            break;
    }
}

void abort_pour() {
    if (drink_pour.state == IDLE) {
        Serial.println("No pour to abort.");
        return;
    }

    set_motor_state(&pump1, MOTOR_OFF);
    set_motor_state(&pump2, MOTOR_OFF);
    set_motor_state(&gantry, MOTOR_UP);
    drink_pour.state = IDLE;
    Serial.println("Pour aborted.");
}