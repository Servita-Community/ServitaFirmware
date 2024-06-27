/**
 * @file pour.h
 * @brief Pour size management, sequencing, and control.
 * @version 0.1
 * @date 2024-05-28
*/

#ifndef POUR_H
#define POUR_H

#include <Arduino.h>
#include <ArduinoJson.h>

#define S_TO_MS 1000

enum pour_states_t {
    IDLE,
    GANTRY_DECENDING,
    POURING,
    GANTRY_ASCENDING,
};

enum drink_t {
    DRINK1,
    DRINK2,
    MIXED,
};

enum pour_size_setting_t {
    DRINK1_POUR_SIZE,
    DRINK2_POUR_SIZE,
    MIXED_POUR_1_SIZE,
    MIXED_POUR_2_SIZE,
};

typedef struct {
    drink_t drink;
    pour_states_t state;
    uint64_t pour_start_time;
} drink_pour_t;


extern uint32_t drink1_pour_size;
extern uint32_t drink2_pour_size;
extern uint32_t mixed1_pour_size;
extern uint32_t mixed2_pour_size;
extern drink_pour_t drink_pour;
extern bool lockout;
extern String get_pour_size();

/**
 * @brief Initialize the pour system by setting the pour sizes and the drink pour state.
*/
void init_pour_system();

/**
 * @brief Set the pour size for a drink.
 * 
 * @param drink The drink to set the pour size for.
 * @param pour_size The pour size to set.
*/
void set_pour_size(pour_size_setting_t setting, uint32_t pour_size);

/**
 * @brief Start the pour sequence for a drink.
 * 
 * @param drink The drink to pour.
*/
void start_pour(drink_t drink);

/**
 * @brief Pour drink sequence driver. Place in main while loop
*/
void pour_seq_loop();

/**
 * @brief Abort the pour sequence.
*/
void abort_pour();

/**
 * @brief validate pour size and conver to ms from s
*/
bool validate_and_convert_size(const char* size, uint32_t& pour_size);

/**
 * @brief Handle a websocket pour json message.
*/
void handle_pour_json(JsonObject payload);

/**
 * @brief Handle a websocket lock json message.
*/
void handle_lock_json(JsonObject payload);

#endif // POUR_H