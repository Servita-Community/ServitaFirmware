#include <FastLED.h>
#include <Arduino.h>
#include <Wire.h>

#include "inc/button.h"
#include "inc/motor.h"
#include "inc/led.h"
#include "inc/pour.h"
#include "inc/server.h"
#include "inc/serial_cmd.h"

#define SDA_PIN 21 // Define IO21 as SDA pin
#define SCL_PIN 22 // Define IO22 as SCL pin


void setup() {
  Serial.begin(115200);
  delay(100);

  init_leds();
  init_limit_switches();
  init_motors();
  init_pour_system();
  init_serial_commands();
  init_buttons();
  init_server();

  Serial.println("Setup complete");

  Wire.begin(SDA_PIN, SCL_PIN); // Initialize I2C communication

  byte error, address;
  int deviceCount = 0;

  Serial.println("Scanning...");

  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Found device at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println(" !");
      deviceCount++;
    }    
    else if (error==4) {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }

  if (deviceCount == 0)
    Serial.println("No I2C devices found\n");
}

void loop() {
  process_serial_command();
  pour_seq_loop();
  button_loop();
  server_loop();
  motor_loop();
}