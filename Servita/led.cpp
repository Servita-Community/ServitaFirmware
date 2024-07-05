#include "inc/led.h"
#include "inc/pins.h"
#include <ArduinoJson.h>
#include <Preferences.h>

RGB board_color;
uint8_t board_brightness;
RGB strip_color;
uint8_t strip_brightness;
uint8_t strip_length;

Preferences led_preferences;

void init_leds() {
    led_preferences.begin("led", false);
    board_brightness = led_preferences.getUInt("boardbrightness", DEFAULT_BOARD_BRIGHTNESS);
    strip_color.r = led_preferences.getUInt("red", 0);
    strip_color.g = led_preferences.getUInt("green", 0);
    strip_color.b = led_preferences.getUInt("blue", 0);
    strip_length = led_preferences.getUInt("length", DEFAULT_STRIP_LENGTH);
    strip_brightness = led_preferences.getUInt("stripbrightness", DEFAULT_STRIP_BRIGHTNESS);

    rmtInit(BOARD_LED_DATA_PIN, RMT_TX_MODE, RMT_MEM_NUM_BLOCKS_1, 10000000);
    rmtInit(ARRAY_LED_DATA_PIN, RMT_TX_MODE, RMT_MEM_NUM_BLOCKS_2, 10000000);

    set_led_color(BOARD_LED_DATA_PIN, RGB::INITIAL_BOOT_COLOR, board_brightness, 1);
    set_led_color(ARRAY_LED_DATA_PIN, strip_color, strip_brightness, strip_length);

    Serial.println("LEDs initialized.");
}

void set_led_color(uint8_t pin, RGB color, uint8_t brightness, uint8_t num_leds) {
    uint16_t num_of_bits = num_leds * 24;
    rmt_data_t led_data[num_of_bits];
    int i = 0;

    uint8_t scaled_red = (color.r * brightness) / 255;
    uint8_t scaled_green = (color.g * brightness) / 255;
    uint8_t scaled_blue = (color.b * brightness) / 255;

    for (int led = 0; led < num_leds; led++) {
        for (int col = 0; col < 3; col++) {
            uint8_t col_val = (col == 1) ? scaled_red : (col == 0) ? scaled_green : scaled_blue;
            for (int bit = 0; bit < 8; bit++) {
                led_data[i].level0 = 1;
                led_data[i].duration0 = (col_val & (1 << (7 - bit))) ? 8 : 4;
                led_data[i].level1 = 0;
                led_data[i].duration1 = (col_val & (1 << (7 - bit))) ? 4 : 8;
                i++;
            }
        }
    }
    rmtWrite(pin, led_data, num_of_bits, RMT_WAIT_FOR_EVER);
}

void set_board_color(RGB color) {
    board_color = color;
    set_led_color(BOARD_LED_DATA_PIN, color, board_brightness, 1);
}

void set_board_brightness(uint8_t brightness) {
    board_brightness = brightness;
    set_led_color(BOARD_LED_DATA_PIN, board_color, brightness, 1);

    led_preferences.begin("led", false);
    led_preferences.putUInt("boardbrightness", board_brightness);
    led_preferences.end();
}

void set_strip_color(RGB color) {
    strip_color = color;
    set_led_color(ARRAY_LED_DATA_PIN, color, strip_brightness, strip_length);

    led_preferences.begin("led", false);
    led_preferences.putUInt("red", color.r);
    led_preferences.putUInt("green", color.g);
    led_preferences.putUInt("blue", color.b);
    led_preferences.end();
}

void set_strip_brightness(uint8_t brightness) {
    strip_brightness = brightness;
    set_led_color(ARRAY_LED_DATA_PIN, strip_color, brightness, strip_length);

    led_preferences.begin("led", false);
    led_preferences.putUInt("stripbrightness", strip_brightness);
    led_preferences.end();
}

void set_strip_length(uint8_t length) {
    if (length > MAXIMUM_STRIP_LENGTH)
        length = MAXIMUM_STRIP_LENGTH;
    
    if (length < strip_length) {
        set_led_color(ARRAY_LED_DATA_PIN, RGB::BLACK, strip_brightness, strip_length);
    }

    set_led_color(ARRAY_LED_DATA_PIN, strip_color, strip_brightness, length);
    strip_length = length;

    led_preferences.begin("led", false);
    led_preferences.putUInt("length", strip_length);
    led_preferences.end();
}

String get_led_status() {
    StaticJsonDocument<256> payload;
    payload["type"] = "ledSettings";
    payload["length"] = strip_length;
    payload["red"] = strip_color.r;
    payload["green"] = strip_color.g;
    payload["blue"] = strip_color.b;
    payload["brightness"] = strip_brightness;
    String jsonString;
    serializeJson(payload, jsonString);
    return jsonString;
}

void handle_led_json(JsonObject payload) {
    if (payload.containsKey("length")) {
        if (payload["length"] == nullptr)       return;

        uint16_t size = atoi(payload["length"]);
        if (size == strip_length)               return;

        Serial.printf("Setting strip length to %u\n", size);
        set_strip_length(size);
    } else if (payload.containsKey("red") || payload.containsKey("green") || payload.containsKey("blue")) {
        RGB new_color = strip_color;

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
        set_strip_color(new_color);
    } else if (payload.containsKey("brightness")) {
        if (payload["brightness"] == nullptr)       return;

        uint8_t brightness = atoi(payload["brightness"]);
        if (brightness == strip_brightness)         return;

        Serial.printf("Setting brightness to %u\n", brightness);
        set_strip_brightness(brightness);
    } else if (payload.containsKey("get")) {
        Serial.println("Requested LED status");
    } else {
        Serial.println("Unknown LED command");
    }
}