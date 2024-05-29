// Version 1.1.12 - May 27, 2024
//    Created from Dan's Blynk code as a starting point.
//    Removed all Blynk integration.
//    Rewrote most mechanical operations to be non-blocking and controlled by flags.
//    Limit switches now operate primarily via hardware interrupts.
//    Serial commands created for operation and hardware debug.

#include <FastLED.h>
#include <SerialCommand.h>

#include <string.h>
#include <stdlib.h>

#include "inc/motor.h"


#include "inc/main_html.h"
#include "inc/captive_html.h"


// WebApp Libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// #include <ESPmDNS.h> -> testing a different method
#include <DNSServer.h>
#include <Preferences.h>

//Webapp Config
const byte DNS_PORT = 53;
AsyncWebServer server(80);
DNSServer dnsServer;

// AP SSID - for captive
Preferences preferences;
const char *ssid = "Servita";

#define userButton 32       // Dispense Button
#define limitSwitchHigh 34  // Top Limit Switch
#define limitSwitchLow 35   // Bottom Limit Switch
#define boardLED 2          // User LED

#define LED_PIN 4    // External RGB LED Data Pin
#define NUM_LEDS 48  // Number of LEDs on External LED Array

#define duoButton 27  //
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
int drinkVariant;
bool deviceLockout = false;

// Flags used by limit switch interrupt
bool endStopHighTrigger = false;
bool endStopLowTrigger = false;

// State variables used for hardware inputs
uint8_t userButtonState;
uint8_t limitSwitchHighState;
uint8_t limitSwitchLowState;
uint8_t duoButtonState;

// Variables used for external LED array control FastLED Library
int ledBrightness = 255;
const int ledMax = 255;
const int ledMin = 75;
int fadeFlag = 0;
CRGB leds[NUM_LEDS];


//Forward definition - Prototyping
void drink1();
void drink2();
void drink3();
void cancelDispense();
void abortDispense();
void dispenseDrink();
void motor2down();
void motor2up();
void motor2stop();
void resetDispenseFlags();
void setPourSize(int pourOption, int time);
void printPourSizes();
void serial_setPourSize();
void serial_setDeviceLockout();
void printButtons();
void readButtons();

SerialCommand sCmd;  // Constructor for serialCommand handler

// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  Serial.println("What?");
}

// Functions called by limit switch interrupt. endStopHighTrigger and endStopLowTrigger flags are used in main loop to perform stop action.
void IRAM_ATTR endStopHigh() {
  endStopHighTrigger = true;
}
void IRAM_ATTR endStopLow() {
  endStopLowTrigger = true;
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
      preferences.begin("wifi", false);
      preferences.putString("ssid", ssid);
      preferences.putString("pass", pass);
      preferences.end();
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
        int size1Val = atoi(parts[1]);
        int size2Val = atoi(parts[2]);

        int s1Mult = size1Val * 1000;
        int s2Mult = size2Val * 1000;
        if (strcmp(parts[1], "drink1") == 0) {
          Serial.println("Pouring Drink 1");
          setPourSize(1, s1Mult);
          drink1();
        } else if (strcmp(parts[1], "drink2") == 0) {
          Serial.println("Pouring Drink 2");
          setPourSize(2, s2Mult);
          drink2();
        } else if (strcmp(parts[1], "drink3") == 0) {
          Serial.println("Pouring Drink 3");
          setPourSize(1, s1Mult);
          setPourSize(2, s2Mult);
          drink3();
        } else if (strcmp(parts[1], "pourCancel") == 0) {
          Serial.println("User Cancel");
          cancelDispense();
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

      preferences.begin("wifi", false);
      preferences.putString("ssid", parts[1]);
      preferences.putString("pass", parts[2]);
      preferences.end();

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

//mDNS Code - To be resolved
/* 
void setupmDNS() {
  // Set up mDNS responder:
  // - first argument is the domain name, in this example
  //   the fully-qualified domain name is "esp32.local"
  // - second argument is the IP address to advertise
  //   we send our IP address on the WiFi network
  if (!MDNS.begin("servita")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
}
*/

void setup() {
  Serial.begin(115200);
  preferences.begin("wifi", false);
  String ssid = preferences.getString("ssid", "");
  String pass = preferences.getString("pass", "");
  preferences.end();


  if (ssid == "" || pass == "") {
    startCaptivePortal();
  } else {
    connectToWiFi(ssid.c_str(), pass.c_str());
  }

  delay(100);
  // Create serial commands and limk them to functions
  sCmd.addCommand("drink1", drink1);
  sCmd.addCommand("drink2", drink2);
  sCmd.addCommand("drink3", drink3);
  sCmd.addCommand("poursize", serial_setPourSize);
  sCmd.addCommand("printpoursizes", printPourSizes);
  sCmd.addCommand("lock", serial_setDeviceLockout);
  sCmd.addCommand("down", motor2down);
  sCmd.addCommand("up", motor2up);
  sCmd.addCommand("s", motor2stop);
  sCmd.addCommand("read", printButtons);
  sCmd.addCommand("cancel", cancelDispense);
  sCmd.addCommand("x", abortDispense);
  sCmd.setDefaultHandler(unrecognized);

  // Initialize motor pins and states
  init_motor(&pump1);
  init_motor(&pump2);
  init_motor(&gantry);

  // Set hardware input pin configurations
  pinMode(limitSwitchLow, INPUT);
  pinMode(limitSwitchHigh, INPUT);
  pinMode(userButton, INPUT_PULLUP);
  pinMode(duoButton, INPUT_PULLUP);

  // Create interrupts for both limit switches
  attachInterrupt(limitSwitchHigh, endStopHigh, FALLING);
  attachInterrupt(limitSwitchLow, endStopLow, FALLING);

  // Send elevator to the top if not already there
  if (digitalRead(limitSwitchHigh) == 1)  set_motor_state(&gantry, MOTOR_UP);
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
  sCmd.readSerial();               // We don't do much, just process serial commands
  dnsServer.processNextRequest();  // wifi related


  // Response to limit switch hardware interrupt
  if (endStopHighTrigger && gantry.state == MOTOR_UP) {
    set_motor_state(&gantry, MOTOR_OFF);
    endStopHighTrigger = false;
    Serial.println("endStopHigh");
  }
  if (endStopLowTrigger && gantry.state == MOTOR_DOWN) {
    set_motor_state(&gantry, MOTOR_OFF);
    endStopLowTrigger = false;
    Serial.println("endStopLow");
  }

  if (dispenseInProgress) dispenseDrink();  // Dispense routine gets called repeatedly when dispenseInProgress flag is high

  readButtons();  // Read inputs on every loop

  // Clean up socket connections
  ws.cleanupClients();
}

// Serial Command Handler to set pour size
void serial_setPourSize() {
  setPourSize(atoi(sCmd.next()), atoi(sCmd.next()));
  printPourSizes();
}

// Serial Command Handler to set lockout state
void serial_setDeviceLockout() {
  deviceLockout = atoi(sCmd.next());
  Serial.println("Lockout State: " + String(deviceLockout));
}

// Set each pour size in ms.
void setPourSize(int pourOption, int time) {
  pourSize[pourOption] = time;
}

// Function to initiate dispense of drink 1. Requires lockout state to be 0 to operate.
void drink1() {
  if (!deviceLockout) {
    drinkVariant = 1;
    dispenseDrink();
  } else Serial.println("Device Lockout Enabled. Dispense Command Rejected.");
}

// Function to initiate dispense of drink 2. Requires lockout state to be 0 to operate.
void drink2() {
  if (!deviceLockout) {
    drinkVariant = 2;
    dispenseDrink();
  } else Serial.println("Device Lockout Enabled. Dispense Command Rejected.");
}

// Function to initiate dispense of drink 3 (mix from both pumps). Requires lockout state to be 0 to operate.
void drink3() {
  if (!deviceLockout) {
    drinkVariant = 3;
    dispenseDrink();
  } else Serial.println("Device Lockout Enabled. Dispense Command Rejected.");
}

// Soft termination of dispense function. Will stop pumps and return elevator to the top position.
void cancelDispense() {
  resetDispenseFlags();
  set_motor_state(&pump1, MOTOR_OFF);
  set_motor_state(&pump2, MOTOR_OFF);
  set_motor_state(&gantry, MOTOR_UP);
}

// Hard termination of dispense function. Will stop pumps and motors in place.
void abortDispense() {
  resetDispenseFlags();
  set_motor_state(&pump1, MOTOR_OFF);
  set_motor_state(&pump2, MOTOR_OFF);
  set_motor_state(&gantry, MOTOR_OFF);
}

// Reads hardware input pins.
void readButtons() {
  limitSwitchHighState = digitalRead(limitSwitchHigh);
  limitSwitchLowState = digitalRead(limitSwitchLow);
  userButtonState = digitalRead(userButton);
  duoButtonState = digitalRead(duoButton);
}

// Prints state of input pins to serial console.
void printButtons() {
  Serial.println("limitSwitchHighState: " + String(limitSwitchHighState));
  Serial.println("limitSwitchLowState: " + String(limitSwitchLowState));
  Serial.println("userButtonState: " + String(userButtonState));
  Serial.println("duoButtonState: " + String(duoButtonState));
}

// Prints current pour size setting to serial console.
void printPourSizes() {
  Serial.println("pour size 0 = " + String(pourSize[0]));
  Serial.println("pour size 1 = " + String(pourSize[1]));
  Serial.println("pour size 2 = " + String(pourSize[2]));
  Serial.println("pour size 3 = " + String(pourSize[3]));
}

// Non/blocking function responsible for initiating, timing, and stopping drink pour.
void pourDrink() {
  if (drinkPouringStarted == false) {
    switch (drinkVariant) {
      case 1:
        set_motor_state(&pump1, MOTOR_ON);
        break;
      case 2:
        set_motor_state(&pump2, MOTOR_ON);
        break;
      case 3:
        set_motor_state(&pump1, MOTOR_ON);
        set_motor_state(&pump2, MOTOR_ON);
        break;
    }
    drinkPouringStarted = true;
    pour_start_time = millis();
  } else if (drinkPouringStarted == true && drinkPouringComplete == false) {
    unsigned long current_time = millis();
    switch (drinkVariant) {
      case 1:
        if (current_time - pour_start_time > pourSize[0])   set_motor_state(&pump1, MOTOR_OFF);

        break;
      case 2:
        if (current_time - pour_start_time > pourSize[1])   set_motor_state(&pump2, MOTOR_OFF);
        break;
      case 3:
        if (current_time - pour_start_time > pourSize[2])   set_motor_state(&pump1, MOTOR_OFF);
        if (current_time - pour_start_time > pourSize[3])   set_motor_state(&pump2, MOTOR_OFF);
        break;
    }

    drinkPouringComplete = (pump1.type == MOTOR_OFF && pump2.type == MOTOR_OFF);
  }
}

// Resets flags used in the dispense function. Called at the end of dispense function, and by cancel & abort funcitons.
void resetDispenseFlags() {
  dispenseInProgress = false;
  carraigeDownStarted = false;
  carraigeReachedBottom = false;
  drinkPouringStarted = false;
  drinkPouringComplete = false;
  carraigeUpStarted = false;
  carraigeReachedTop = false;
}

// Non/blocking function responsible for choreographing elevator and pumps for main dispensing feature
void dispenseDrink() {
  dispenseInProgress = true;
  if (carraigeDownStarted == false) {
    set_motor_state(&gantry, MOTOR_DOWN);
    Serial.println("carraige lowering");
    carraigeDownStarted = true;
  }
  if (carraigeDownStarted == true && limitSwitchLowState == 0 && carraigeReachedBottom == false) {
    carraigeReachedBottom = true;
    Serial.println("carraige reached bottom");
  }
  if (carraigeReachedBottom == true && drinkPouringComplete == false) {
    pourDrink();
  }
  if (drinkPouringComplete == true && carraigeUpStarted == false) {
    set_motor_state(&gantry, MOTOR_UP);
    carraigeUpStarted = true;
    Serial.println("carraige raising");
  }
  if (carraigeUpStarted == true && limitSwitchHighState == 0 && carraigeReachedTop == false) {
    carraigeReachedTop = true;
    Serial.println("carraige reached top");
  }
  if (carraigeReachedTop == true) {
    resetDispenseFlags();
  }
}

void motor2down() {   set_motor_state(&gantry, MOTOR_DOWN); }
void motor2up() {     set_motor_state(&gantry, MOTOR_UP);   }
void motor2stop() {   set_motor_state(&gantry, MOTOR_OFF);  }
