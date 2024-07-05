#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Arduino.h>
#include "driver/rmt.h"


void led_init(rmt_channel_t channel, gpio_num_t gpio_num);
void led_set_color(const uint8_t *data, size_t num_leds);

#endif // LED_CONTROL_H