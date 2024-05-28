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

#define motor1In1 17  // Motor Driver Control Pins
#define motor1In2 5   //
#define motor1En1 16  // \
                      //
#define motor2In3 19  //
#define motor2In4 21  //
#define motor2En2 18  // \
                      //
#define motor3In5 15  //
#define motor3In6 13  //
#define motor3En3 12  // \
                      //
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
bool elevatorMovingDown = false;
bool elevatorMovingUp = false;
bool pump1running = false;
bool pump2running = false;
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
void motor2down();
void motor2up();
void motor2stop();
void pump1start();
void pump1stop();
void pump2start();
void pump2stop();
void dispenseDrink();
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
      preferences.putString("ssid", ssid);
      preferences.putString("pass", pass);
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
        motor2up();
      } else if (strcmp(parts[1], "mCarDown") == 0) {
        motor2down();
      } else if (strcmp(parts[1], "stop") == 0) {
        motor2stop();
      } else if (strcmp(parts[1], "mCarHome") == 0) {
        motor2up();
      }
    } else if (parts.size() == 4 && strcmp(parts[1], "start") == 0) {

      if (strcmp(parts[2], "rPump1") == 0) {
        pump1start();
      } else if (strcmp(parts[2], "rPump2")) {
        pump2start();
      }

    } else if (parts.size() == 4 && strcmp(parts[1], "stop") == 0) {
      if (strcmp(parts[2], "rPump1") == 0) {
        pump1stop();
      } else if (strcmp(parts[2], "rPump2") == 0) {
        pump2stop();
      }
    } else if (parts.size() == 3 && strcmp(parts[0], "net") == 0) {

      preferences.putString("ssid", parts[1]);
      preferences.putString("pass", parts[2]);

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

  // Set all motor control pins to output
  pinMode(motor1In1, OUTPUT);
  pinMode(motor1In2, OUTPUT);
  pinMode(motor1En1, OUTPUT);
  pinMode(motor2In3, OUTPUT);
  pinMode(motor2In4, OUTPUT);
  pinMode(motor2En2, OUTPUT);
  pinMode(motor3In5, OUTPUT);
  pinMode(motor3In6, OUTPUT);
  pinMode(motor3En3, OUTPUT);

  // Set initial off states for motor outputs
  digitalWrite(motor1In1, LOW);
  digitalWrite(motor1In2, LOW);
  digitalWrite(motor1En1, LOW);
  digitalWrite(motor2In3, LOW);
  digitalWrite(motor2In4, LOW);
  digitalWrite(motor2En2, LOW);
  digitalWrite(motor3In5, LOW);
  digitalWrite(motor3In6, LOW);
  digitalWrite(motor3En3, LOW);

  // Set hardware input pin configurations
  pinMode(limitSwitchLow, INPUT);
  pinMode(limitSwitchHigh, INPUT);
  pinMode(userButton, INPUT_PULLUP);
  pinMode(duoButton, INPUT_PULLUP);

  // Create interrupts for both limit switches
  attachInterrupt(limitSwitchHigh, endStopHigh, FALLING);
  attachInterrupt(limitSwitchLow, endStopLow, FALLING);

  // Send elevator to the top if not already there
  if (digitalRead(limitSwitchHigh) == 1) motor2up();
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
  if (endStopHighTrigger && elevatorMovingUp) {
    motor2stop();
    endStopHighTrigger = false;
    Serial.println("endStopHigh");
  }
  if (endStopLowTrigger && elevatorMovingDown) {
    motor2stop();
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
  pump1stop();
  pump2stop();
  motor2up();
}

// Hard termination of dispense function. Will stop pumps and motors in place.
void abortDispense() {
  resetDispenseFlags();
  pump1stop();
  pump2stop();
  motor2stop();
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
        pump1start();
        break;
      case 2:
        pump2start();
        break;
      case 3:
        pump1start();
        pump2start();
        break;
    }
    drinkPouringStarted = true;
    pour_start_time = millis();
  } else if (drinkPouringStarted == true && drinkPouringComplete == false) {
    unsigned long current_time = millis();
    switch (drinkVariant) {
      case 1:
        if (current_time - pour_start_time > pourSize[0]) pump1stop();
        break;
      case 2:
        if (current_time - pour_start_time > pourSize[1]) pump2stop();
        break;
      case 3:
        if (current_time - pour_start_time > pourSize[2]) pump1stop();
        if (current_time - pour_start_time > pourSize[3]) pump2stop();
        break;
    }
    if (pump1running == false && pump2running == false) {
      drinkPouringComplete = true;
    }
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
    motor2down();
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
    motor2up();
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

// Sets elevator motor in downward motion
void motor2down() {
  digitalWrite(motor2In3, HIGH);
  digitalWrite(motor2In4, LOW);
  digitalWrite(motor2En2, HIGH);
  elevatorMovingDown = true;
  elevatorMovingUp = false;
  Serial.println("down");
}

// Sets elevator motor in upward motion
void motor2up() {
  digitalWrite(motor2In3, LOW);
  digitalWrite(motor2In4, HIGH);
  digitalWrite(motor2En2, HIGH);
  elevatorMovingDown = false;
  elevatorMovingUp = true;
  Serial.println("up");
}

// Stops elevator motor
void motor2stop() {
  digitalWrite(motor2In3, LOW);
  digitalWrite(motor2In4, LOW);
  digitalWrite(motor2En2, HIGH);
  elevatorMovingDown = false;
  elevatorMovingUp = false;
  Serial.println("stop");
}

// Starts Pump 1
void pump1start() {
  digitalWrite(motor1In1, HIGH);
  digitalWrite(motor1In2, LOW);
  digitalWrite(motor1En1, HIGH);
  pump1running = true;
  Serial.println("pump 1 start");
}

// Stops Pump 1
void pump1stop() {
  digitalWrite(motor1In1, LOW);
  digitalWrite(motor1In2, LOW);
  digitalWrite(motor1En1, HIGH);
  pump1running = false;
  Serial.println("pump 1 stop");
}

// Starts Pump 2
void pump2start() {
  digitalWrite(motor3In5, HIGH);
  digitalWrite(motor3In6, LOW);
  digitalWrite(motor3En3, HIGH);
  pump2running = true;
  Serial.println("pump 2 start");
}

// Stops Pump 2
void pump2stop() {
  digitalWrite(motor3In5, LOW);
  digitalWrite(motor3In6, LOW);
  digitalWrite(motor3En3, HIGH);
  pump2running = false;
  Serial.println("pump 2 stop");
}
