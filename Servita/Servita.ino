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
#include <SinricPro.h>
#include "inc/ServitaBartender.h"


void setup() {
  Serial.begin(115200);
  delay(100);
  set_pins_based_on_board_version();
  init_expansion();
  init_leds();
  init_limit_switches();
  init_motors();
  init_pour_system();
  init_serial_commands();
  init_buttons();
  init_server();
  init_sinric();

    // ModeController
  if (valid_sinric_credentials()) {
    ServitaBartender &servitaBartender = SinricPro[device_id];
    servitaBartender.onSetMode("serve-drink", on_set_mode);

    SinricPro.onConnected([]{ Serial.printf("[SinricPro]: Connected\r\n"); });
    SinricPro.onDisconnected([]{ Serial.printf("[SinricPro]: Disconnected\r\n"); });
    SinricPro.begin(app_key, app_secret);

    Serial.println("Sinric credentials valid... initializing...");
  } else {
    Serial.println("Sinric credentials not valid... skipping initialization...");
  }
}

void loop() {
  process_serial_command();
  pour_seq_loop();
  button_loop();
  server_loop();
  motor_loop();
  SinricPro.handle();
}