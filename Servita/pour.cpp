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

uint8_t drink1_pour_size;
uint8_t drink2_pour_size;
uint8_t mixed1_pour_size;
uint8_t mixed2_pour_size;
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
}

void set_pour_size(pour_size_setting_t setting, uint8_t pour_size) {
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