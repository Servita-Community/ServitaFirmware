#include "inc/button.h"
#include "inc/motor.h"
#include "inc/led.h"
#include "inc/pour.h"
#include "inc/server.h"
#include "inc/serial_cmd.h"
#include "inc/pins.h"
#include "inc/expansion.h"
#include "Arduino.h"


// Sinric Pro Integration
#include <SinricPro.h>
#include "inc/ServitaBartender.h"
#include "Preferences.h"


#ifdef ESP32
  #include <WiFi.h>
#endif
Preferences sinric_information;

bool is_enabled = false;
String APP_KEY;
String APP_SECRET;
String DEVICE_ID;
void get_sinric_information(String app_key, String app_secret, String device_id) {
  sinric_information.begin("sinric", true);
  app_key = sinric_information.getString("app_key", "");
  app_secret = sinric_information.getString("app_secret", "");
  device_id = sinric_information.getString("device_id", "");
  sinric_information.end();
}
void save_sinric_information(const char* app_key, const char* app_secret, const char* device_id) {
  sinric_information.begin("sinric", false);
  sinric_information.putString("app_key", app_key);
  sinric_information.putString("app_secret", app_secret);
  sinric_information.putString("device_id", device_id);
  sinric_information.end();
  //Serial.println("Saved SinricPro information");
}
//

ServitaBartender &servitaBartender = SinricPro[DEVICE_ID];

std::map<String, String> globalModes;

bool onSetMode(const String& deviceId, const String& instance, String &mode) {
  Serial.printf("[Device: %s]: Modesetting for \"%s\" set to mode %s\r\n", deviceId.c_str(), instance.c_str(), mode.c_str());
  globalModes[instance] = mode;
  String pour_sizes = get_pour_size();
  StaticJsonDocument<256> sizes;
  DeserializationError error = deserializeJson(sizes, pour_sizes);
  if (error) {
    Serial.printf("Error parsing pour sizes: %s", error.c_str());
    return false;
  }
  
  const char* size1 = sizes["p1"];
  const char* size2 = sizes["p2"];
  const char* size3 = sizes["mixed1"];
  const char* size4 = sizes["mixed2"];

  StaticJsonDocument<256> cmd;
  if (mode == "drink1") {
    cmd["drink"] = "drink1";
    cmd["size"] = size1;
    handle_pour_json(cmd);
    
  } else if (mode == "drink2") {
    cmd["drink"] = "drink2";
    cmd["size"] = size2;
    handle_pour_json(cmd);
    
  } else if (mode == "drink3") {
    cmd["drink"] = "drink3";
    cmd["size1"] = size1;
    cmd["size2"] = size4;
    handle_pour_json(cmd);
    
  } else if (mode == "cancel") {
    cmd["drink"] = "pourCancel";
    handle_pour_json(cmd);
  } else {
    Serial.printf("Invalid mode: %s", mode.c_str());
    return false;
  }
  return true;
}

void updateMode(String instance, String mode) {
  servitaBartender.sendModeEvent(instance, mode, "PHYSICAL_INTERACTION");
}

void setup_SinricPro() {

  servitaBartender.onSetMode("serve-drink", onSetMode);

  SinricPro.onConnected([]{ Serial.printf("[SinricPro]: Connected\r\n"); });
  SinricPro.onDisconnected([]{ Serial.printf("[SinricPro]: Disconnected\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}



void setup() {
  Serial.begin(115200);
  delay(100);

  set_pins_based_on_board_version();
  init_expansion();
  init_leds();
  init_limit_switches();
  init_motors();
  init_pour_system();
  init_serial_commands();
  init_buttons();
  init_server();
  get_sinric_information(APP_KEY, APP_SECRET, DEVICE_ID);
  if (is_enabled == true){
    setup_SinricPro();
  }
  Serial.println("Setup complete");
}

void loop() {
  process_serial_command();
  pour_seq_loop();
  button_loop();
  server_loop();
  motor_loop();
  if (is_enabled == true){
    SinricPro.handle();
  }
}