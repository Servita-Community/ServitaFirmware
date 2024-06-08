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

void save_credentials(const char *ssid, const char *pass);
void delete_credentials();
void get_credentials(String *ssid, String *pass);
void on_ws_event(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
bool connect_to_wifi(const char *ssid, const char *pass);
void init_server();
void server_loop();


#endif  // SERVER_H