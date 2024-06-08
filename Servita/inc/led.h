/**
 * @file led.h
 * @brief LED handling for Servita board LED and external LED array.
 * @version 0.1
 * @date 2024-06-08
 */
#ifndef LED_H
#define LED_H

#include <FastLED.h>

#define BOARD_LED_DATA_PIN 2
#define ARRAY_LED_DATA_PIN 4

#define ERROR_COLOR CRGB::Red
#define MOTOR_TIMEOUT_COLOR CRGB::Orange
#define NETWORK_ERROR_COLOR CRGB::Yellow
#define CONNECTED_COLOR CRGB::Green
#define LOOKING_FOR_CONNECTION_COLOR CRGB::Blue
#define NO_CONNECTION_COLOR CRGB::Purple

enum BoardLEDState {
    ERROR,
    MOTOR_TIMEOUT,
    NETWORK_ERROR,
    CONNECTED,
    LOOKING_FOR_CONNECTION,
    NO_CONNECTION,
    PARTY_MODE
};

extern BoardLEDState led_state;
extern uint16_t led_array_length;


void init_leds();
void led_loop();
void update_strip_length(uint16_t length);


#endif // LED_H