/**
 * @file server.h
 * @brief This file contains the credentials for the WiFi network, as well as the captive portal functions.
 * @version 0.1
 * @date 2024-06-08
*/

#ifndef SERVER_H
#define SERVER_H

#include <ESPAsyncWebServer.h>
#include <Arduino.h>
#include <ArduinoJson.h>

extern bool hosted_locally;
extern void handle_pour_json(JsonObject payload);
extern void get_sinric_information(bool is_enabled, String *APP_KEY, String *APP_SECRET, String *DEVICE_ID);
extern void save_sinric_information(const char *app_key, const char *app_secret, const char *device_id);
extern void delete_sinric_information();
extern String get_pour_size();

void save_credentials(const char *ssid, const char *pass);
void delete_credentials();
void get_credentials(String *ssid, String *pass);
void on_ws_event(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
bool connect_to_wifi(const char *ssid, const char *pass);
void handle_net_json(AsyncWebSocketClient *client, JsonObject payload);
void init_server();
void server_loop();
void handle_sinric_json(AsyncWebSocketClient *client, JsonObject payload);




#endif  // SERVER_H