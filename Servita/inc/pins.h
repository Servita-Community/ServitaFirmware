/**
 * @file pins.h
 * @brief Pin definitions based on board version.
 * @version 0.1
 * @date 2024-07-05
 */

#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

extern uint8_t BUTTON1_PIN;
extern uint8_t BUTTON2_PIN;
extern uint8_t BOARD_LED_DATA_PIN;
extern uint8_t ARRAY_LED_DATA_PIN;
extern uint8_t PUMP1_HIGH_PIN;
extern uint8_t PUMP1_LOW_PIN;
extern uint8_t PUMP1_ENABLE_PIN;
extern uint8_t PUMP2_HIGH_PIN;
extern uint8_t PUMP2_LOW_PIN;
extern uint8_t PUMP2_ENABLE_PIN;
extern uint8_t GANTRY_UP_PIN;
extern uint8_t GANTRY_DOWN_PIN;
extern uint8_t GANTRY_ENABLE_PIN;
extern uint8_t LIMIT_SWITCH_TOP;
extern uint8_t LIMIT_SWITCH_BOTTOM;

void set_pins_based_on_board_version();

#endif // PINS_H