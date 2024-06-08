/**
 * @file credentials.cpp
 * @brief This file contains the credentials for the WiFi network, as well as the captive portal functions.
 * @version 0.1
 * @date 2024-06-04
 */

#include "inc/captive.h"
#include "inc/captive_html.h"
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <Preferences.h>
#include <WiFi.h>

AsyncWebServer captive_server(80);
DNSServer captive_dns;
Preferences preferences;
bool captive = false;

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

void start_captive_portal() {
    captive = true;
    Serial.println("Starting Captive Portal");
    WiFi.softAP("Servita");
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP Address: ");
    Serial.println(IP);

    captive_dns.start(53, "*", IP);

    captive_server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("User Connected");
        request->send_P(200, "text/html", captive_html);
    });

    captive_server.on("/setWiFi", HTTP_POST, [](AsyncWebServerRequest *request) {
        String ssid, pass;

        if (request->hasParam("ssid", true) && request->hasParam("password", true)) {
            ssid = request->getParam("ssid", true)->value();
            pass = request->getParam("password", true)->value();
            save_credentials(ssid.c_str(), pass.c_str());
            request->send(200, "text/plain", "Credentials saved. Restarting ESP.");
            delay(3000);
            ESP.restart();
        } else {
            request->send(400, "text/plain", "Invalid Request");
        }
    });

    captive_server.begin();
}