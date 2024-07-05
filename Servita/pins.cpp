/**
* @file pins.c
* @brief Pin definitions based on board version.
* @version 0.1
* @date 2024-07-05
*/

#include "inc/pins.h"
#include "inc/brd_version.h"

// Define default pin values (Compatible with v1.0 board)
uint8_t BUTTON1_PIN = 32;
uint8_t BUTTON2_PIN = 27;
uint8_t BOARD_LED_DATA_PIN = 2;
uint8_t ARRAY_LED_DATA_PIN = 4;
uint8_t PUMP1_HIGH_PIN = 17;
uint8_t PUMP1_LOW_PIN = 5;
uint8_t PUMP1_ENABLE_PIN = 16;
uint8_t PUMP2_HIGH_PIN = 15;
uint8_t PUMP2_LOW_PIN = 13;
uint8_t PUMP2_ENABLE_PIN = 12;
uint8_t GANTRY_UP_PIN = 21;
uint8_t GANTRY_DOWN_PIN = 19;
uint8_t GANTRY_ENABLE_PIN = 18;
uint8_t LIMIT_SWITCH_TOP = 34;
uint8_t LIMIT_SWITCH_BOTTOM = 35;

void set_pins_based_on_board_version() {
    String board_version = get_board_version();

    if (board_version == "v0.0") {
        BUTTON1_PIN = 32;
        BUTTON2_PIN = 27;
        BOARD_LED_DATA_PIN = 2;
        ARRAY_LED_DATA_PIN = 4;
        PUMP1_HIGH_PIN = 17;
        PUMP1_LOW_PIN = 5;
        PUMP1_ENABLE_PIN = 16;
        PUMP2_HIGH_PIN = 15;
        PUMP2_LOW_PIN = 13;
        PUMP2_ENABLE_PIN = 12;
        GANTRY_UP_PIN = 21;
        GANTRY_DOWN_PIN = 19;
        GANTRY_ENABLE_PIN = 18;
        LIMIT_SWITCH_TOP = 34;
        LIMIT_SWITCH_BOTTOM = 35;
    } else if (board_version == "v1.0") {
        BUTTON1_PIN = 32;
        BUTTON2_PIN = 27;
        BOARD_LED_DATA_PIN = 2;
        ARRAY_LED_DATA_PIN = 4;
        PUMP1_HIGH_PIN = 17;
        PUMP1_LOW_PIN = 5;
        PUMP1_ENABLE_PIN = 16;
        PUMP2_HIGH_PIN = 15;
        PUMP2_LOW_PIN = 13;
        PUMP2_ENABLE_PIN = 12;
        GANTRY_UP_PIN = 21;
        GANTRY_DOWN_PIN = 19;
        GANTRY_ENABLE_PIN = 18;
        LIMIT_SWITCH_TOP = 34;
        LIMIT_SWITCH_BOTTOM = 35;
    } else {
        Serial.println("Unknown board version, using default pin values.");
    }
}