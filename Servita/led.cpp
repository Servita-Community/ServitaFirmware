/**
 * @file led.cpp
 * @brief LED handling for Servita board LED and external LED array.
 * @version 0.1
 * @date 2024-06-08
 */
#include "inc/led.h"
#include <ArduinoJson.h>
#include <FastLED.h>

CRGB strip_leds[MAXIMUM_STRIP_LED_LENGTH];
CRGB strip_color;
uint16_t strip_length;
uint8_t led_brightness;

CRGB board_led;
BoardLEDState board_state = NO_CONNECTION;

Preferences led_preferences;


void init_leds() {
    led_preferences.begin("led", false);
    strip_color.r = led_preferences.getUInt("red", 0);
    strip_color.g = led_preferences.getUInt("green", 0);
    strip_color.b = led_preferences.getUInt("blue", 0);
    strip_length = led_preferences.getUInt("length", DEFAULT_STRIP_LED_LENGTH);
    led_brightness = led_preferences.getUInt("brightness", DEFAULT_STRIP_LED_BRIGHTNESS);
    led_preferences.end();

    Serial.printf("LED strip color preferences (R,G,B): (%u, %u, %u)\n", strip_color.r, strip_color.g, strip_color.b);
    Serial.printf("LED strip length preference: %u\n", strip_length);
    Serial.printf("LED strip brightness preference: %u\n", led_brightness);

    FastLED.addLeds<WS2812, ARRAY_LED_DATA_PIN, GRB>(strip_leds, MAXIMUM_STRIP_LED_LENGTH);
    FastLED.addLeds<SK6812, BOARD_LED_DATA_PIN, GRB>(&board_led, 1);

    fill_solid(strip_leds, strip_length, strip_color);
    board_led = NO_CONNECTION_COLOR;
    FastLED.show(led_brightness);

    Serial.println("LEDs initialized");
}

void set_led_strip_length(uint16_t length) {
    if (length > MAXIMUM_STRIP_LED_LENGTH)
        length = MAXIMUM_STRIP_LED_LENGTH;

    if (length < strip_length) {
        fill_solid(strip_leds + length, strip_length - length, CRGB::Black);
    }

    strip_length = length;
    fill_solid(strip_leds, strip_length, strip_color);
    FastLED.show(led_brightness);

    led_preferences.begin("led", false);
    led_preferences.putUInt("length", strip_length);
    led_preferences.end();
}

void set_led_strip_color(CRGB color) {
    strip_color = color;
    fill_solid(strip_leds, strip_length, strip_color);
    FastLED.show(led_brightness);

    led_preferences.begin("led", false);
    led_preferences.putUInt("red", strip_color.r);
    led_preferences.putUInt("green", strip_color.g);
    led_preferences.putUInt("blue", strip_color.b);
    led_preferences.end();
}

void set_led_strip_brightness(uint8_t brightness) {
    led_brightness = brightness;
    FastLED.show(led_brightness);

    led_preferences.begin("led", false);
    led_preferences.putUInt("brightness", led_brightness);
    led_preferences.end();
}

void handle_led_json(JsonObject payload) {
    if (payload.containsKey("length")) {
        if (payload["length"] == nullptr)       return;

        uint16_t size = atoi(payload["length"]);
        if (size == strip_length)               return;

        Serial.printf("Setting strip length to %u\n", size);
        set_led_strip_length(size);
    } else if (payload.containsKey("red") || payload.containsKey("green") || payload.containsKey("blue")) {
        CRGB new_color = strip_color;

        if (payload["red"] != nullptr) {
            uint8_t r = atoi(payload["red"]);
            new_color.r = r > 255 ? 255 : r;
        }
        if (payload["green"] != nullptr) {
            uint8_t g = atoi(payload["green"]);
            new_color.g = g > 255 ? 255 : g;
        }
        if (payload["blue"] != nullptr) {
            uint8_t b = atoi(payload["blue"]);
            new_color.b = b > 255 ? 255 : b;
        }
        
        if (new_color == strip_color) return;
        Serial.printf("Setting color to (%u, %u, %u)\n", new_color.r, new_color.g, new_color.b);
        set_led_strip_color(new_color);
    } else if (payload.containsKey("brightness")) {
        if (payload["brightness"] == nullptr)       return;

        uint8_t brightness = atoi(payload["brightness"]);
        if (brightness == led_brightness)         return;

        Serial.printf("Setting brightness to %u\n", brightness);
        set_led_strip_brightness(brightness);
    } else {
        Serial.println("Unknown LED command");
        return;
    }
}