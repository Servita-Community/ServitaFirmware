#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "driver/rmt.h"


#define MAXIMUM_STRIP_LENGTH 120
#define DEFAULT_BOARD_BRIGHTNESS 128
#define DEFAULT_STRIP_LENGTH 60
#define DEFAULT_STRIP_BRIGHTNESS 128

struct RGB {
    union {
        struct {
            union {
                uint8_t red;
                uint8_t r;
            };
            union {
                uint8_t green;
                uint8_t g;
            };
            union {
                uint8_t blue;
                uint8_t b;
            };
        };
        uint8_t raw[3];
    };

    /// Default constructor
    /// @warning Default values are UNINITIALIZED!
    inline RGB() __attribute__((always_inline)) = default;

    /// Allow construction from red, green, and blue
    /// @param ir input red value
    /// @param ig input green value
    /// @param ib input blue value
    constexpr RGB(uint8_t ir, uint8_t ig, uint8_t ib)  __attribute__((always_inline))
        : r(ir), g(ig), b(ib)
    {
    }

    /// Allow construction from 32-bit (really 24-bit) bit 0xRRGGBB color code
    /// @param colorcode a packed 24 bit color code
    constexpr RGB(uint32_t colorcode)  __attribute__((always_inline))
    : r((colorcode >> 16) & 0xFF), g((colorcode >> 8) & 0xFF), b((colorcode >> 0) & 0xFF)
    {
    }

    /// Define an operator for ==
    constexpr bool operator==(const RGB& other) const {
        return (r == other.r && g == other.g && b == other.b);
    }

    typedef enum {
        LOCKOUT_COLOR=0xFF0000,  // Red
        INITIAL_BOOT_COLOR=0xFFFFFF,  // White
        LOCAL_WEBSERVER_COLOR=0x00FF00,  // Green
        EXTERNAL_WEBSERVER_COLOR=0x0000FF,  // Blue
        POUR_DRINK_1_COLOR=0xFFFF00,  // Yellow
        POUR_DRINK_2_COLOR=0x800080,  // Purple
        POUR_DRINK_MIXED_COLOR=0xFFC0CB,  // Pink

        BLACK=0x000000,
    } led_color_states;
};

extern RGB board_color;
extern uint8_t board_brightness;
extern RGB strip_color;
extern uint8_t strip_brightness;
extern uint8_t strip_length;
extern bool array_fried;
extern String led_array_checker;

void init_leds();
void set_led_color(uint8_t pin, RGB color, uint8_t brightness, uint8_t num_leds);
void set_board_color(RGB color);
void set_board_brightness(uint8_t brightness);
void set_strip_color(RGB color);
void set_strip_brightness(uint8_t brightness);
void set_strip_length(uint8_t length);
void handle_led_json(JsonObject payload);
void handle_set_board_led(String params);
String get_led_status();

#endif // LED_H