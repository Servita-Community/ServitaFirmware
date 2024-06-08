// Version 1.1.12 - May 27, 2024
//    Created from Dan's Blynk code as a starting point.
//    Removed all Blynk integration.
//    Rewrote most mechanical operations to be non-blocking and controlled by flags.
//    Limit switches now operate primarily via hardware interrupts.
//    Serial commands created for operation and hardware debug.

#include <FastLED.h>
#include <string.h>
#include <stdlib.h>

#include "inc/button.h"
#include "inc/motor.h"
#include "inc/pour.h"
#include "inc/captive.h"
#include "inc/serial_cmd.h"
#include "inc/main_html.h"
#include "inc/captive_html.h"


// WebApp Libraries
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>

//Webapp Config
const byte DNS_PORT = 53;
AsyncWebServer server(80);
DNSServer dnsServer;

// AP SSID - for captive
const char *ssid = "Servita";

#define boardLED 2          // User LED

#define LED_PIN 4    // External RGB LED Data Pin
#define NUM_LEDS 48  // Number of LEDs on External LED Array

#define ExtIO2 26     //
#define ExtIO3 25     //

// Flags & variables used by non-blocking dispense function
bool dispenseInProgress = false;
bool carraigeDownStarted = false;
bool carraigeReachedBottom = false;
bool drinkPouringStarted = false;
bool drinkPouringComplete = false;
bool carraigeUpStarted = false;
bool carraigeReachedTop = false;
unsigned long pour_start_time;
unsigned long current_time;
int pourSize[] = { 3000, 3000, 1500, 1500 };
bool deviceLockout = false;

// Variables used for external LED array control FastLED Library
int ledBrightness = 255;
const int ledMax = 255;
const int ledMin = 75;
int fadeFlag = 0;
CRGB leds[NUM_LEDS];

// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  Serial.println("What?");
}

// WebApp Integration
// AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// CaptivePortal Function
void startCaptivePortal() {
  Serial.println("Starting Captive Portal");

  // Start the AP with no password
  WiFi.softAP(ssid, "");
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(IP);

  dnsServer.start(53, "*", IP);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.print("User Connected");
    request->send_P(200, "text/html", captive_html);
  });

  server.on("/setWiFi", HTTP_POST, [](AsyncWebServerRequest *request) {
    String ssid;
    String pass;
    if (request->hasParam("ssid", true) && request->hasParam("password", true)) {
      String ssid = request->getParam("ssid", true)->value();
      String pass = request->getParam("password", true)->value();

      save_credentials(ssid.c_str(), pass.c_str());
      request->send(200, "text/plain", "Received SSID: " + ssid + "\nPassword: " + pass);
      delay(3000);
      ESP.restart();  // Restart ESP to connect with new credentials
      // Optionally connect to WiFi or save credentials here
    } else {
      request->send(400, "text/plain", "Invalid Request");
    }
  });

  server.begin();
}

char *trim(char *str) {
  char *end;
  // Trim leading space
  while (isspace((unsigned char)*str)) str++;
  if (*str == 0)  // All spaces?
    return str;
  // Trim trailing space
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end)) end--;
  // Write new null terminator
  end[1] = '\0';
  return str;
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("WebSocket client connected");
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.println("WebSocket client disconnected");
  } else if (type == WS_EVT_DATA) {
    Serial.print("Data received: ");
    Serial.println(String((char *)data));
    String receivedData = String((char *)data);


    // Tokenize the data
    std::vector<char *> parts;
    char *token = strtok((char *)data, ",");
    while (token != NULL) {
      token = trim(token);
      parts.push_back(token);
      token = strtok(NULL, ",");
    }

  
    if (parts.size() == 5 && strcmp(parts[0], "pour") == 0) {
      if (strcmp(parts[0], "pour") == 0) {
        // Handle pour-related actions
        int size1Val = atoi(parts[2]);
        int size2Val = atoi(parts[3]);

        int s1Mult = size1Val * 1000;
        int s2Mult = size2Val * 1000;
        if (strcmp(parts[1], "drink1") == 0) {
          Serial.println("Pouring Drink 1");
          Serial.println("Setting Pour Size: " + String(s1Mult) + "ms");
          set_pour_size(DRINK1_POUR_SIZE, s1Mult);
          if (!deviceLockout) {
            start_pour(DRINK1);
          }
          else {
            Serial.println("Device Lockout Enabled. Dispense Command Rejected.");
          }
        } else if (strcmp(parts[1], "drink2") == 0) {
          Serial.println("Pouring Drink 2");
          Serial.println("Setting Pour Size: " + String(s2Mult) + "ms");
          set_pour_size(DRINK2_POUR_SIZE, s2Mult);
          if (!deviceLockout) {
            start_pour(DRINK2);
          }
          else {
            Serial.println("Device Lockout Enabled. Dispense Command Rejected.");
          }
        } else if (strcmp(parts[1], "drink3") == 0) {
          Serial.println("Pouring Drink 3");
          Serial.println("Setting Pour Size: " + String(s1Mult) + "ms");
          Serial.println("Setting Pour Size: " + String(s2Mult) + "ms");
          set_pour_size(MIXED_POUR_1_SIZE, s1Mult);
          set_pour_size(MIXED_POUR_2_SIZE, s2Mult);
          if (!deviceLockout) {
            start_pour(MIXED);
          }
          else {
            Serial.println("Device Lockout Enabled. Dispense Command Rejected.");
          }
        } else if (strcmp(parts[1], "pourCancel") == 0) {
          Serial.println("User Cancel");
          abort_pour();
        }
      }
    } else if (parts.size() == 3 && strcmp(parts[0], "manual") == 0) {
      if (strcmp(parts[1], "mCarUp") == 0) {
        set_motor_state(&gantry, MOTOR_UP);
      } else if (strcmp(parts[1], "mCarDown") == 0) {
        set_motor_state(&gantry, MOTOR_DOWN);
      } else if (strcmp(parts[1], "stop") == 0) {
        set_motor_state(&gantry, MOTOR_OFF);
      } else if (strcmp(parts[1], "mCarHome") == 0) {
        set_motor_state(&gantry, MOTOR_UP);
      }
    } else if (parts.size() == 4 && strcmp(parts[1], "start") == 0) {

      if (strcmp(parts[2], "rPump1") == 0) {
        set_motor_state(&pump1, MOTOR_ON);
      } else if (strcmp(parts[2], "rPump2")) {
        set_motor_state(&pump2, MOTOR_ON);
      }

    } else if (parts.size() == 4 && strcmp(parts[1], "stop") == 0) {
      if (strcmp(parts[2], "rPump1") == 0) {
        set_motor_state(&pump1, MOTOR_OFF);
      } else if (strcmp(parts[2], "rPump2") == 0) {
        set_motor_state(&pump2, MOTOR_OFF);
      }
    } else if (parts.size() == 3 && strcmp(parts[0], "net") == 0) {
      save_credentials(parts[1], parts[2]);
      ESP.restart();
    } else if (parts.size() == 3 && strcmp(parts[0], "lock") == 0) {
      if (strcmp(parts[1], "lock") == 0) {
        deviceLockout = true;
      } else if (strcmp(parts[1], "unlock")) {
        deviceLockout = false;
      }
    } else if (parts.size() == 3 && strcmp(parts[0], "lnum") == 0) {
      // rgb locgic here | Number of ext LEDS

    } else if (parts.size() == 5 && strcmp(parts[0], "led") == 0) {
      // RGB Logic here | colors for EXT LED
    } else if (parts.size() == 3 && strcmp(parts[0], "brightness") == 0) {
      // brightness logic here (ext lED)
    }

    else {
      Serial.println("Insufficient data received");
    }
  }
  Serial.println();
}


void initWebSocket() {
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
}
void connectToWiFi(const char *ssid, const char *pass) {
  WiFi.setHostname("servita.local");  // Set the desired hostname here
  WiFi.begin(ssid, pass);

  Serial.print("Connecting to WiFi..");
  int maxAttempts = 10;  // Maximum number of attempts to connect to WiFi
  int attempt = 0;

  while (WiFi.status() != WL_CONNECTED && attempt < maxAttempts) {
    delay(500);
    Serial.print(".");
    attempt++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    // setupmDNS();
    Serial.println("Connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    // Start server to serve HTML page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send_P(200, "text/html", main_html);
    });
    server.begin();
  } else {
    Serial.println("Failed to connect to WiFi. Please check credentials.");
    // Optionally restart the Captive Portal to re-enter credentials
    startCaptivePortal();
  }
}

void setup() {
  Serial.begin(115200);
  String ssid, pass;
  get_credentials(&ssid, &pass);

  if (ssid == "" || pass == "") {
    startCaptivePortal();
  } else {
    connectToWiFi(ssid.c_str(), pass.c_str());
  }

  delay(100);

  // Iniitialize systems
  init_limit_switches();
  init_motors();
  init_pour_system();
  init_serial_commands();
  init_buttons();

  // WebApp - Start WebSocket
  initWebSocket();
  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", main_html);
  });
  server.begin();
}

void loop() {
  process_serial_command();
  dnsServer.processNextRequest();  // wifi related

  pour_seq_loop();
  button_loop();

  ws.cleanupClients();
}