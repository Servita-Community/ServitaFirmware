/**
 * @file brd_version.cpp
 * @brief Board version information.
 * @version 0.1
 * @date 2024-07-05
*/

#include "inc/brd_version.h"
#include <Preferences.h>

Preferences board_prefs;
String board_version = "NONE";


void save_board_version(String version) {
    board_prefs.begin("board", false);
    board_prefs.putString("version", version);
    board_prefs.end();
    Serial.printf("Saved board version: %s\n", version.c_str());
}

String get_board_version() {
    board_prefs.begin("board", true);
    board_version = board_prefs.getString("version", "NONE");
    board_prefs.end();
    if (board_version == "NONE") {
        Serial.println("No board version found");
        return "NONE";
    }
    Serial.printf("Retrieved board version: %s\n", board_version.c_str());

    return board_version;
}

unsigned long hashString(const String &str) {
    unsigned long hash = 5381;
    for (int i = 0; i < str.length(); i++) {
        hash = ((hash << 5) + hash) + str[i]; // hash * 33 + c
    }
    return hash & 0xFFFFFFFF; // Ensure the hash is 32 bits
}

void handle_save_brd_version(String params) {
    int firstSpaceIndex = params.indexOf(' ');
    String password;
    String version;

    if (firstSpaceIndex != -1) {
        password = params.substring(0, firstSpaceIndex);
        version = params.substring(firstSpaceIndex + 1);
    } else {
        password = params;
        version = "";
    }

    if (hashString(password) == 300951455) {
        save_board_version(version);
    } else {
        Serial.println("Invalid password");
    }
}