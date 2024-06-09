/**
 * @file led.h
 * @brief LED handling for Servita board LED and external LED array.
 * @version 0.1
 * @date 2024-06-08
 */
#ifndef LED_H
#define LED_H

#include <ArduinoJson.h>
#include <FastLED.h>
#include <Preferences.h>

#define BOARD_LED_DATA_PIN 2
#define ARRAY_LED_DATA_PIN 4
#define MAXIMUM_STRIP_LED_LENGTH 120
#define DEFAULT_STRIP_LED_LENGTH 60
#define DEFAULT_BOARD_LED_BRIGHTNESS 128
#define DEFAULT_STRIP_LED_BRIGHTNESS 128

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

void init_leds();
void set_led_strip_length(uint16_t length);
void set_led_strip_color(CRGB color);
void set_led_strip_brightness(uint8_t brightness);
void handle_led_json(JsonObject payload);

#endif // LED_H