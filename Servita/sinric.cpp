#include "inc/sinric.h"
#include "inc/pour.h"
#include <Preferences.h>
#include <SinricPro.h>
#include "inc/ServitaBartender.h"

Preferences sinric_preferences;

String app_key;
String app_secret;
String device_id;

bool valid_sinric_credentials() {
    return app_key.length() > 0 && app_secret.length() > 0 && device_id.length() > 0;
}

void init_sinric() {
    sinric_preferences.begin("sinric", true);
    device_id = sinric_preferences.getString("deviceid", "");
    app_key = sinric_preferences.getString("appkey", "");
    app_secret = sinric_preferences.getString("appsecret", "");
    sinric_preferences.end();

    if (app_key.length() == 0 || app_secret.length() == 0 || device_id.length() == 0) {
        return;
    }

    if (valid_sinric_credentials()) {
        ServitaBartender &servitaBartender = SinricPro[device_id];
        servitaBartender.onSetMode("serve-drink", on_set_mode);

        SinricPro.onConnected([]{ Serial.printf("[SinricPro]: Connected\r\n"); });
        SinricPro.onDisconnected([]{ Serial.printf("[SinricPro]: Disconnected\r\n"); });
        SinricPro.begin(app_key, app_secret);

        Serial.println("Sinric credentials valid... initializing...");
    } else {
        Serial.println("Sinric credentials not valid... skipping initialization...");
    }
}

bool on_set_mode(const String& deviceId, const String& instance, String &mode) {
    Serial.printf(
        "[Device: %s]: Modesetting for \"%s\" set to mode %s\r\n",
        deviceId.c_str(),
        instance.c_str(),
        mode.c_str()
    );

    if (instance == "serve-drink") {
        if (mode == "drink1")           start_pour(DRINK1);
        else if (mode == "drink2")      start_pour(DRINK2);
        else if (mode == "drink3")      start_pour(MIXED);
        else if (mode == "cancel")      abort_pour();
        else {
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

    bool changed = false;

    if (payload.containsKey("appKey")) {
        app_key = payload["appKey"].as<String>();
        sinric_preferences.putString("appkey", app_key);
        Serial.printf("Set App Key to: %s\r\n", app_key.c_str());
        changed = true;
    } else {
        Serial.println("App Key not found in payload");
    }

    if (payload.containsKey("appSecret")) {
        app_secret = payload["appSecret"].as<String>();
        sinric_preferences.putString("appsecret", app_secret);
        Serial.printf("Set App Secret to: %s\r\n", app_secret.c_str());
        changed = true;
    } else {
        Serial.println("App Secret not found in payload");
    }

    if (payload.containsKey("deviceID")) {
        device_id = payload["deviceID"].as<String>();
        sinric_preferences.putString("deviceid", device_id);
        Serial.printf("Set Device ID to: %s\r\n", device_id.c_str());
        changed = true;
    } else {
        Serial.println("Device ID not found in payload");
    }

    sinric_preferences.end();

    if (changed && valid_sinric_credentials()) {
        Serial.println("Restarting to apply sinric credential changes...");
        ESP.restart();
    }

    if (!changed) {
        Serial.println("No changes made to sinric credentials");
        return;
    }

    Serial.println("Sinric credentials updated, but not valid... Skipping restart...");
}

void sinric_loop() {
    SinricPro.handle();
}