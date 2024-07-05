#include "inc/button.h"
#include "inc/motor.h"
#include "inc/led.h"
#include "inc/pour.h"
#include "inc/server.h"
#include "inc/serial_cmd.h"
#include "inc/pins.h"
#include "Arduino.h"

void setup() {
  Serial.begin(115200);
  delay(100);

  set_pins_based_on_board_version();
  init_leds();
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
  motor_loop();
}