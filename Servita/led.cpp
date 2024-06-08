/**
 * @file led.cpp
 * @brief LED handling for Servita board LED and external LED array.
 * @version 0.1
 * @date 2024-06-08
 */
#include "inc/led.h"
#include <FastLED.h>


BoardLEDState led_state = NO_CONNECTION;
uint16_t led_array_length = 60;


void init_leds() {
    FastLED.addLeds<WS2812B, BOARD_LED_DATA_PIN, GRB>(leds, 1).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<WS2812B, ARRAY_LED_DATA_PIN, GRB>(leds, led_array_length).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(128);
    fill_solid(leds, 1, CRGB::Black);
    fill_solid(leds + 1, led_array_length, CRGB::Black);
    FastLED.show();
}