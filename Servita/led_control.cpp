#include "inc/led_control.h"

#define WS2815_T0H_NS (300)
#define WS2815_T0L_NS (1090)
#define WS2815_T1H_NS (1090)
#define WS2815_T1L_NS (320)

static const char *TAG = "LED_CONTROL";
static rmt_channel_t g_channel;

static void ws2815_prepare_rmt_data(const uint8_t *led_data, rmt_item32_t *rmt_items, size_t num_bytes) {
    int item_idx = 0;
    for (int byte_idx = 0; byte_idx < num_bytes; byte_idx++) {
        uint8_t byte = led_data[byte_idx];
        for (int bit = 7; bit >= 0; bit--) {
            if (byte & (1 << bit)) {
                // Bit is 1
                rmt_items[item_idx].duration0 = WS2815_T1H_NS / 10;
                rmt_items[item_idx].level0 = 1;
                rmt_items[item_idx].duration1 = WS2815_T1L_NS / 10;
                rmt_items[item_idx].level1 = 0;
            } else {
                // Bit is 0
                rmt_items[item_idx].duration0 = WS2815_T0H_NS / 10;
                rmt_items[item_idx].level0 = 1;
                rmt_items[item_idx].duration1 = WS2815_T0L_NS / 10;
                rmt_items[item_idx].level1 = 0;
            }
            item_idx++;
        }
    }
}

void led_init(rmt_channel_t channel, gpio_num_t gpio_num) {
    g_channel = channel;
    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(gpio_num, channel);
    config.clk_div = 2;
    rmt_config(&config);
    rmt_driver_install(config.channel, 0, 0);
    ESP_LOGI(TAG, "LED initialized on GPIO %d, channel %d", gpio_num, channel);
}

void led_set_color(const uint8_t *data, size_t num_leds) {
    size_t num_bytes = num_leds * 3;
    size_t num_items = num_bytes * 8;

    rmt_item32_t *items = (rmt_item32_t) malloc(num_items * sizeof(rmt_item32_t));
    ws2815_prepare_rmt_data(data, items, num_bytes);

    rmt_write_items(g_channel, items, num_items, true);
    rmt_wait_tx_done(g_channel, portMAX_DELAY);

    free(items);
}