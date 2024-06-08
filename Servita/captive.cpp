/**
 * @file credentials.cpp
 * @brief This file contains the credentials for the WiFi network, as well as the captive portal functions.
 * @version 0.1
 * @date 2024-06-04
*/

#include "inc/captive.h"
#include <Preferences.h>

Preferences preferences;

void save_credentials(const char *ssid, const char *pass) {
    preferences.begin("wifi", false);
    preferences.putString("ssid", ssid);
    preferences.putString("pass", pass);
    preferences.end();
    Serial.printf("Saved WiFi credentials for ssid: %s\n", ssid);
}

void delete_credentials() {
    preferences.begin("wifi", false);
    preferences.remove("ssid");
    preferences.remove("pass");
    preferences.end();
    Serial.println("Deleted WiFi credentials");
}

void get_credentials(String *ssid, String *pass) {
    preferences.begin("wifi", true);
    *ssid = preferences.getString("ssid", "");
    *pass = preferences.getString("pass", "");
    preferences.end();
    if (ssid->length() == 0) {
        Serial.println("No WiFi credentials found");
        return;
    }
    Serial.printf("Retrieved WiFi credentials for ssid: %s\n", ssid->c_str());
}