/**
 * @file server.cpp
 * @brief This file contains the server functions for the Servita project.
 * @version 0.1
 * @date 2024-06-08
 */

#include "inc/server.h"
#include "inc/main_html.h"
#include "inc/pour.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <Preferences.h>
#include <ArduinoJson.h>


AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
Preferences wifi_preferences;
DNSServer local_dns;

void save_credentials(const char *ssid, const char *pass) {
    wifi_preferences.begin("wifi", false);
    wifi_preferences.putString("ssid", ssid);
    wifi_preferences.putString("pass", pass);
    wifi_preferences.end();
    Serial.printf("Saved WiFi credentials for ssid: %s\n", ssid);
}

void delete_credentials() {
    wifi_preferences.begin("wifi", false);
    wifi_preferences.remove("ssid");
    wifi_preferences.remove("pass");
    wifi_preferences.end();
    Serial.println("Deleted WiFi credentials");
}

void get_credentials(String *ssid, String *pass) {
    wifi_preferences.begin("wifi", true);
    *ssid = wifi_preferences.getString("ssid", "");
    *pass = wifi_preferences.getString("pass", "");
    wifi_preferences.end();
    if (ssid->length() == 0) {
        Serial.println("No WiFi credentials found");
        return;
    }
    Serial.printf("Retrieved WiFi credentials for ssid: %s\n", ssid->c_str());
}

bool connect_to_wifi(const char *ssid, const char *pass) {
    WiFi.setHostname("servita.local");
    WiFi.begin(ssid, pass);

    Serial.print("Connecting to WiFi..");
    int maxAttempts = 10;
    int attempt = 0;

    while (WiFi.status() != WL_CONNECTED && attempt < maxAttempts) {
        delay(500);
        Serial.print(".");
        attempt++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected to WiFi!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        return true;
    } else {
        Serial.println("Failed to connect to WiFi. Please check credentials.");
        WiFi.disconnect();
        return false;
    }
}

void on_ws_event(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    } else if (type == WS_EVT_DISCONNECT) {
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
    } else if (type == WS_EVT_ERROR) {
        Serial.printf("WebSocket client #%u error\n", client->id());
    } else if (type == WS_EVT_DATA) {
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
            data[len] = 0;
            Serial.printf("WebSocket client #%u message: %s\n", client->id(), (char *)data);

            // Parse JSON message
            StaticJsonDocument<512> doc;
            DeserializationError error = deserializeJson(doc, (char*)data);

            if (error) {
                Serial.print("deserializeJson() failed: ");
                Serial.println(error.c_str());
                return;
            }

            const char* type = doc["type"];
            JsonObject payload = doc["payload"];

            if (strcmp(type, "pour") == 0) {
                handle_pour_json(payload);
            } else if (strcmp(type, "led") == 0) {
                // handleLED(payload);
            } else if (strcmp(type, "brightness") == 0) {
                // handleBrightness(payload);
            } else if (strcmp(type, "manual") == 0) {
                // handleManual(payload);
            } else if (strcmp(type, "net") == 0) {
                // handleNet(payload);
            } else if (strcmp(type, "lock") == 0) {
                // handleLock(payload);
            } else if (strcmp(type, "lnum") == 0) {
                // handleLNum(payload);
            } else {
                Serial.println("Unknown message type");
            }
        }
    }
}

void setup_server_http() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", main_html);
    });
}

void init_server() {
    bool run_locally = true;
    String ssid, pass;
    get_credentials(&ssid, &pass);

    if (ssid.length() != 0 || pass.length() != 0 ) {
        run_locally = !connect_to_wifi(ssid.c_str(), pass.c_str());
    }

    if (run_locally) {
        Serial.println("Starting Local AP...");
        WiFi.softAP("Servita");
        IPAddress IP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(IP);
        local_dns.start(53, "*", IP);
        Serial.println("Local DNS server started...");
    }

    setup_server_http();
    ws.onEvent(on_ws_event);
    server.addHandler(&ws);
    server.begin();
}

void server_loop() {
    ws.cleanupClients();
    local_dns.processNextRequest();
}