/**
 * @file server.cpp
 * @brief This file contains the server functions for the Servita project.
 * @version 0.1
 * @date 2024-06-08
 */

#include "inc/server.h"
#include "inc/main_html.h"
#include "inc/motor.h"
#include "inc/pour.h"
#include "inc/led.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <Preferences.h>
#include <ArduinoJson.h>

// String get_pour_size();
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
Preferences wifi_preferences;
DNSServer local_dns;
bool hosted_locally = true;

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
                handle_led_json(payload);
                String ledStatus = get_led_status();
                client->text(ledStatus);
            } else if (strcmp(type, "manual") == 0) {
                handle_motor_json(payload);
            } else if (strcmp(type, "net") == 0) {
                handle_net_json(client, payload);
            } else if (strcmp(type, "lock") == 0) {
                handle_lock_json(payload);
            } else if (strcmp(type, "getPourSize") == 0) {
                String pourSizes = get_pour_size();
                client->text(pourSizes);
            } else if (strcmp(type, "changePourSize") == 0) {
                const char* drink = payload["drink"];
                if (drink == nullptr) {
                    Serial.println("Missing drink field.");
                    return;
                }

                if (strcmp(drink, "drink1") == 0) {
                    const char* sizeStr = payload["size"];
                    uint32_t size;
                    if (!validate_and_convert_size(sizeStr, size)) return;
                    set_pour_size(DRINK1_POUR_SIZE, size);
                } else if (strcmp(drink, "drink2") == 0) {
                    const char* sizeStr = payload["size"];
                    uint32_t size;
                    if (!validate_and_convert_size(sizeStr, size)) return;
                    set_pour_size(DRINK2_POUR_SIZE, size);
                } else if (strcmp(drink, "drink3") == 0) {
                    uint32_t size1, size2;
                    const char* sizeStr1 = payload["size1"];
                    const char* sizeStr2 = payload["size2"];
                    if (!validate_and_convert_size(sizeStr1, size1)) return;
                    if (!validate_and_convert_size(sizeStr2, size2)) return;

                    set_pour_size(MIXED_POUR_1_SIZE, size1);
                    set_pour_size(MIXED_POUR_2_SIZE, size2);
                } else {
                    Serial.println("Unknown drink type.");
                }   

                String pourSizes = get_pour_size();
                client->text(pourSizes);
            }
            else {
                Serial.println("Unknown message type");
            }
        }
    }
}

void handle_net_json(AsyncWebSocketClient *client, JsonObject payload) {
    const char* ssid = payload["ssid"];
    const char* pass = payload["password"];

    if (ssid == nullptr || pass == nullptr) {
        Serial.println("Invalid WiFi credentials");
        return;
    }

    save_credentials(ssid, pass);
    delay(2000);  // Small delay to ensure message is sent
    ESP.restart();
}

void init_server() {
    String ssid, pass;
    get_credentials(&ssid, &pass);

    if (ssid.length() != 0 || pass.length() != 0 ) {
        hosted_locally = !connect_to_wifi(ssid.c_str(), pass.c_str());
    }

    if (hosted_locally) {
        Serial.println("Starting Local AP...");
        WiFi.softAP("Servita");
        IPAddress IP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(IP);
        local_dns.start(53, "*", IP);
        Serial.println("Local DNS server started...");
    }

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", main_html);
    });
    ws.onEvent(on_ws_event);
    server.addHandler(&ws);
    server.begin();

    set_board_color(hosted_locally ? RGB::LOCAL_WEBSERVER_COLOR : RGB::EXTERNAL_WEBSERVER_COLOR);
}

void server_loop() {
    ws.cleanupClients();
    local_dns.processNextRequest();
}