#pragma once

#ifndef SINRIC_H_
#define SINRIC_H_

#include <WiFi.h>
#include <ArduinoJson.h>

extern String app_key;
extern String app_secret;
extern String device_id;

/**
 * @brief 
 * 
 */
bool valid_sinric_credentials();

/**
 * @brief 
 */
void init_sinric();

/**
 * @brief 
 * 
 * @param deviceId 
 * @param instance 
 * @param mode 
 * @return true 
 * @return false 
 */
bool on_set_mode(const String& deviceId, const String& instance, String &mode);

/**
 * @brief 
 * 
 */
void handle_sinric_json(JsonObject payload);

#endif // SINRIC_H_