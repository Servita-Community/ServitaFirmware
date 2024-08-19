/**
 * @file pour.cpp
 * @brief Pour size management, sequencing, and control.
 * @version 0.1
 * @date 2024-05-28
*/
#include "inc/pour.h"
#include "inc/motor.h"
#include "inc/led.h"
#include "inc/server.h"
#include "inc/button.h"
#include "inc/pins.h"
#include "inc/expansion.h"
#include <Preferences.h>
#include <ArduinoJson.h>


uint32_t drink1_pour_size;
uint32_t drink2_pour_size;
uint32_t mixed1_pour_size;
uint32_t mixed2_pour_size;
drink_pour_t drink_pour;
bool lockout = false;

Preferences pour_preferences;

void init_pour_system() {
    pour_preferences.begin("pour", false);
    drink1_pour_size = pour_preferences.getUInt("drink1", 0);
    drink2_pour_size = pour_preferences.getUInt("drink2", 0);
    mixed1_pour_size = pour_preferences.getUInt("mixed1", 0);
    mixed2_pour_size = pour_preferences.getUInt("mixed2", 0);
    pour_preferences.end();

    drink_pour.drink = DRINK1;
    drink_pour.state = IDLE;
    drink_pour.pour_start_time = 0;
}



String get_pour_size() {
    StaticJsonDocument<256> payload;
    payload["type"] = "pourSize";
    payload["p1"] = String(drink1_pour_size);

    if (expansion_type == DUO_BOARD) {
        payload["p2"] = String(drink2_pour_size);
        payload["mixed1"] = String(mixed1_pour_size);
        payload["mixed2"] = String(mixed2_pour_size);
    }
    String jsonString;
    serializeJson(payload, jsonString);
    return jsonString;
}

void set_pour_size(pour_size_setting_t setting, uint32_t pour_size) {
    bool opened = pour_preferences.begin("pour", false);
    switch (setting) {
        case DRINK1_POUR_SIZE: {
            drink1_pour_size = pour_size;
            pour_preferences.putUInt("drink1", drink1_pour_size);
            break;
        }
        case DRINK2_POUR_SIZE: {
            drink2_pour_size = pour_size;
            pour_preferences.putUInt("drink2", drink2_pour_size);
            break;
        }
        case MIXED_POUR_1_SIZE: {
            mixed1_pour_size = pour_size;
            pour_preferences.putUInt("mixed1", mixed1_pour_size);
            break;
        }
        case MIXED_POUR_2_SIZE: {
            mixed2_pour_size = pour_size;
            pour_preferences.putUInt("mixed2", mixed2_pour_size);
            break;
        }
    }
    pour_preferences.end();
}

void start_pour(drink_t drink) {
    if (drink != DRINK1 && expansion_type != DUO_BOARD) {
        Serial.println("Duo Board required for drinks 2 & 3.");
        return;
    }

    if (drink_pour.state != IDLE) {
        Serial.println("Pour already in progress.");
        return;
    }

    if (lockout) {
        Serial.println("Motor lockout in effect, cannot pour.");
        return;
    }

    drink_pour.drink = drink;
    set_motor_state(&gantry, MOTOR_DOWN);
    set_board_color(
        drink == DRINK1 ? RGB::POUR_DRINK_1_COLOR : 
        drink == DRINK2 ? RGB::POUR_DRINK_2_COLOR : RGB::POUR_DRINK_MIXED_COLOR
    );
    drink_pour.state = GANTRY_DECENDING;
    gantry_state = GANTRY_POURING;
    Serial.printf("Starting pour for drink: %d\n", drink);
}

void pour_seq_loop() {
    if (lockout)        return;

    switch (drink_pour.state) {
        case GANTRY_DECENDING:
            if (digitalRead(LIMIT_SWITCH_BOTTOM) == LOW) {
                drink_pour.pour_start_time = (uint64_t) millis();

                if (is_button_pressed(BUTTON1) || is_button_pressed(BUTTON2)) {
                    Serial.println("Button based pour cancel detected. Aborting pour...");
                    abort_pour();
                    break;
                }

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
                gantry_state = GANTRY_NONE;
                set_board_color(hosted_locally ? RGB::LOCAL_WEBSERVER_COLOR : RGB::EXTERNAL_WEBSERVER_COLOR);
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

    if (expansion_type == DUO_BOARD)        set_motor_state(&pump2, MOTOR_OFF);

    if (!lockout) {
        set_motor_state(&gantry, MOTOR_UP);
        drink_pour.state = GANTRY_ASCENDING;
        set_board_color(hosted_locally ? RGB::LOCAL_WEBSERVER_COLOR : RGB::EXTERNAL_WEBSERVER_COLOR);
    } else {
        Serial.println("Motor lockout in effect, will not raise gantry.");
        drink_pour.state = IDLE;
    }

    Serial.println("Pour aborted.");
}

bool validate_and_convert_size(const char* sizeStr, uint32_t& size) {
    if (sizeStr == nullptr || !isDigit(sizeStr[0])) {
        Serial.println("Invalid pour size.");
        return false;
    }
    size = atoi(sizeStr) * S_TO_MS;
    return true;
}

void handle_pour_json(JsonObject payload) {
    const char* drink = payload["drink"];
    if (drink == nullptr) {
        Serial.println("Missing drink field.");
        return;
    }

    uint32_t size1, size2;
    bool drink1 = strcmp(drink, "drink1") == 0;
    bool drink2 = strcmp(drink, "drink2") == 0;

    if (drink1 || drink2) {
        const char* sizeStr = payload["size"];
        if (!validate_and_convert_size(sizeStr, size1)) return;

        Serial.printf("Setting pour size for %s to: %u ms\n", drink, size1);
        set_pour_size(drink1 ? DRINK1_POUR_SIZE : DRINK2_POUR_SIZE, size1);
        start_pour(drink1 ? DRINK1 : DRINK2);
    } else if (strcmp(drink, "drink3") == 0) {
        const char* size1Str = payload["size1"];
        const char* size2Str = payload["size2"];
        if (!validate_and_convert_size(size1Str, size1) || !validate_and_convert_size(size2Str, size2)) return;

        Serial.printf("Setting pour sizes for mixed drink to: %u ms and %u ms\n", size1, size2);
        set_pour_size(MIXED_POUR_1_SIZE, size1);
        set_pour_size(MIXED_POUR_2_SIZE, size2);
        start_pour(MIXED);
    } else if (strcmp(drink, "pourCancel") == 0) {
        Serial.println("Aborting pour.");
        abort_pour();
    } else {
        Serial.println("Unknown drink type.");
    }
}

void handle_lock_json(JsonObject payload) {
    const char *action = payload["action"];
    if (strcmp(action, "lock") == 0) {
        abort_pour();
        lockout = true;
        set_board_color(RGB::LOCKOUT_COLOR);
    } else if (strcmp(action, "unlock") == 0) {
        lockout = false;
        set_board_color(hosted_locally ? RGB::LOCAL_WEBSERVER_COLOR : RGB::EXTERNAL_WEBSERVER_COLOR);
    }
}