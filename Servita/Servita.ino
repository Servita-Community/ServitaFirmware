//#include "inc/button.h"
//#include "inc/motor.h"
// #include "inc/led.h"
//#include "inc/pour.h"
//#include "inc/server.h"
//#include "inc/serial_cmd.h"
#include "inc/pins.h"
#include "inc/led_control.h"
#include "Arduino.h"


static rmt_channel_t g_channel;

void setup() {
  Serial.begin(115200);
  delay(100);

  set_pins_based_on_board_version();

  led_init(g_channel, (gpio_num_t) ARRAY_LED_DATA_PIN);

  uint8_t red_color[3] = {0xFF, 0x00, 0x00}; // Red
  uint8_t green_color[3] = {0x00, 0xFF, 0x00}; // Green
  uint8_t blue_color[3] = {0x00, 0x00, 0xFF}; // Blue

  while (1) {
    led_set_color(red_color, 30);
    delay(1000);
    led_set_color(green_color, 30);
    delay(1000);
    led_set_color(blue_color, 30);
    delay(1000);
  }
  /*
  init_leds();
  init_limit_switches();
  init_motors();
  init_pour_system();
  init_serial_commands();
  init_buttons();
  init_server();

  Serial.println("Setup complete");
  */
}

void loop() {
  /*
  process_serial_command();
  pour_seq_loop();
  button_loop();
  server_loop();
  motor_loop();
  */
}