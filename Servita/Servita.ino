#include <FastLED.h>

#include "inc/button.h"
#include "inc/motor.h"
#include "inc/pour.h"
#include "inc/server.h"
#include "inc/serial_cmd.h"

#define boardLED 2          // User LED
#define LED_PIN 4           // External RGB LED Data Pin
#define NUM_LEDS 30         // Number of LEDs on External LED Array
#define ExtIO2 26           //
#define ExtIO3 25           //

// Flags & variables used by non-blocking dispense function
bool deviceLockout = false;

// Variables used for external LED array control FastLED Library
int ledBrightness = 255;
const int ledMax = 255;
const int ledMin = 75;
int fadeFlag = 0;
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);

  delay(100);

  // Iniitialize systems
  init_limit_switches();
  init_motors();
  init_pour_system();
  init_serial_commands();
  init_buttons();
  init_server();

  // Initialize the FastLED library
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(128); // Set initial brightness to 50%

  fill_rainbow(leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  FastLED.show();
  delay(1000);
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(1000);
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(1000);
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();

  Serial.println("Setup complete");
}

void loop() {
  process_serial_command();
  pour_seq_loop();
  button_loop();
  server_loop();
}