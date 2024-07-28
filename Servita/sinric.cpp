#include "inc/sinric.h"
#include "inc/pour.h"
#include "Preferences.h"

Preferences sinric_preferences;

String app_key;
String app_secret;
String device_id;

ServitaBartender *servitaBartender = nullptr;

void init_sinric() {
    sinric_preferences.begin("sinric", true);
    app_key = sinric_preferences.getString("appkey", "");
    app_secret = sinric_preferences.getString("appsecret", "");
    device_id = sinric_preferences.getString("deviceid", "");
    sinric_preferences.end();

    if (servitaBartender != nullptr)    delete servitaBartender;
    servitaBartender = new ServitaBartender(device_id);

    servitaBartender->onSetMode("serve-drink", on_set_mode);

    SinricPro.onConnected([]{ Serial.printf("[SinricPro]: Connected\r\n"); });
    SinricPro.onDisconnected([]{ Serial.printf("[SinricPro]: Disconnected\r\n"); });
    SinricPro.begin(app_key, app_secret);
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

void handle_sinric_json(JsonObject payload) {
    sinric_preferences.begin("sinric", false);

    if (payload.containsKey("app_key")) {
        app_key = payload["app_key"].as<String>();
        sinric_preferences.putString("appkey", app_key);
    }

    if (payload.containsKey("app_secret")) {
        app_secret = payload["app_secret"].as<String>();
        sinric_preferences.putString("appsecret", app_secret);
    }

    if (payload.containsKey("device_id")) {
        device_id = payload["device_id"].as<String>();
        sinric_preferences.putString("deviceid", device_id);
    }

    sinric_preferences.end();
}

void sinric_loop() {
    SinricPro.handle();
}