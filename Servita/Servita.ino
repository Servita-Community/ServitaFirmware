#include <FastLED.h>

#include "inc/button.h"
#include "inc/motor.h"
#include "inc/pour.h"
#include "inc/server.h"
#include "inc/serial_cmd.h"

#define boardLED 2          // User LED
#define LED_PIN 4           // External RGB LED Data Pin
#define NUM_LEDS 48         // Number of LEDs on External LED Array
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

  Serial.println("Setup complete");
}

void loop() {
  process_serial_command();
  pour_seq_loop();
  button_loop();
  server_loop();
}