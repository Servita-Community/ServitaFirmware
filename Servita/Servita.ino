#include "inc/button.h"
#include "inc/motor.h"
#include "inc/led.h"
#include "inc/pour.h"
#include "inc/server.h"
#include "inc/serial_cmd.h"
#include "inc/pins.h"
#include "inc/expansion.h"
#include "inc/sinric.h"
#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  delay(100);
  set_pins_based_on_board_version();
  Serial.println("pins success");
  init_expansion();
  Serial.println("expansion success");
  init_leds();
  Serial.println("led success");
  init_limit_switches();
  Serial.println("limit switch success");
  init_motors();
  Serial.println("motor success");
  init_pour_system();
  Serial.println("pour success");
  Serial.println("commands");
  init_serial_commands();
  Serial.println("commands success");
  init_buttons();
  Serial.println("buttons success");
  init_server();
  Serial.println("server success");
  init_sinric();
  Serial.println("sinric Success");

  Serial.println("Setup complete");
}

void loop() {
  process_serial_command();
  pour_seq_loop();
  button_loop();
  server_loop();
  motor_loop();
  sinric_loop();
}