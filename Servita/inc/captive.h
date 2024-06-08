/**
 * @file credentials.h
 * @brief This file contains the credentials for the WiFi network, as well as the captive portal functions.
 * @version 0.1
 * @date 2024-06-04
*/

#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <Arduino.h>


void save_credentials(const char *ssid, const char *pass);
void delete_credentials();
void get_credentials(String *ssid, String *pass);
void start_captive_portal();

extern bool captive;



#endif  // CREDENTIALS_H