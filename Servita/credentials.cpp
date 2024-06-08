/**
 * @file credentials.cpp
 * @brief This file contains the credentials for the WiFi network, as well as the captive portal functions.
 * @version 0.1
 * @date 2024-06-04
*/

#include "inc/credentials.h"


void delete_credentials() {
    // Delete the stored WiFi credentials
    WiFi.disconnect(true);
    Serial.println("Deleted stored WiFi credentials.");
}