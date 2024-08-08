#include <SinricPro.h>
#include "inc/sinric.h"
#include "inc/ServitaBartender.h"
#include "inc/pour.h"
#include <Preferences.h>

Preferences sinric_preferences;

String app_key;
String app_secret;
String device_id;

ServitaBartender *servitaBartender = nullptr;

void init_sinric() {
    sinric_preferences.begin("sinric", true);
    app_key = sinric_preferences.getString("appKey", "");
    app_secret = sinric_preferences.getString("appSecret", "");
    device_id = sinric_preferences.getString("deviceId", "");


    sinric_preferences.end();

    if (servitaBartender != nullptr) {
      delete servitaBartender;
      servitaBartender = new ServitaBartender(device_id);
      servitaBartender->onSetMode("serve-drink", on_set_mode);

      SinricPro.onConnected([]{ Serial.printf("[SinricPro]: Connected\r\n"); });
      SinricPro.onDisconnected([]{ Serial.printf("[SinricPro]: Disconnected\r\n"); });
      SinricPro.begin(app_key, app_secret);
    } 
    if (strcmp(app_key.c_str(), "") == 0) {
      Serial.println("Sinric not yet configured.");
    } else {
      delete servitaBartender;
      servitaBartender = new ServitaBartender(device_id);
      servitaBartender->onSetMode("serve-drink", on_set_mode);

      SinricPro.onConnected([]{ Serial.printf("[SinricPro]: Connected\r\n"); });
      SinricPro.onDisconnected([]{ Serial.printf("[SinricPro]: Disconnected\r\n"); });
      SinricPro.begin(app_key, app_secret);

    }
    
}

bool on_set_mode(const String& deviceId, const String& instance, String &mode) {
    if (instance == "serve-drink") {
        if (mode == "drink1") {
            start_pour(DRINK1);
        } else if (mode == "drink2") {
            start_pour(DRINK2);
        } else if (mode == "drink3") {
            start_pour(MIXED);
        } else if (mode == "cancel") {
            abort_pour();
        } else {
            Serial.printf("[Device: %s]: Invalid mode: %s\r\n", deviceId.c_str(), mode.c_str());
            return false;
        }
    } else {
        Serial.printf("[Device: %s]: Invalid instance: %s\r\n", deviceId.c_str(), instance.c_str());
        return false;
    }
    
    return true;
}

void handle_sinric(const char *appKey, const char *appSecret, const char *deviceId) {

    sinric_preferences.begin("sinric", false);

    sinric_preferences.putString("appKey", appKey);
    sinric_preferences.putString("appSecret", appSecret);
    sinric_preferences.putString("deviceId", deviceId);
    
    sinric_preferences.end();
}

void sinric_loop() {
    SinricPro.handle();
}