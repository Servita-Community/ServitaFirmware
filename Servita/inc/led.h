/**
 * @file led.h
 * @brief LED handling for Servita board LED and external LED array.
 * @version 0.2
 * @date 2024-06-09
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
#define DEFAULT_BRIGHTNESS 128

#define LOCKOUT_COLOR CRGB::Red
#define INITIAL_BOOT_COLOR CRGB::White
#define LOCAL_WEBSERVER_COLOR CRGB::Green
#define EXTERNAL_WEBSERVER_COLOR CRGB::Blue
#define POUR_DRINK_1_COLOR CRGB::Yellow
#define POUR_DRINK_2_COLOR CRGB::Purple
#define POUR_DRINK_MIXED_COLOR CRGB::Pink

void init_leds();
void set_led_strip_length(uint16_t length);
void set_led_strip_color(CRGB color);
void set_led_strip_brightness(uint8_t brightness);
void set_board_led(CRGB color);
void handle_led_json(JsonObject payload);
String get_led_status();

#endif // LED_H