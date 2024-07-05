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

void save_board_version(const char *version) {
    board_prefs.begin("board", false);
    board_prefs.putString("version", version);
    board_prefs.end();
    Serial.printf("Saved board version: %s\n", version);
}

void get_board_version() {
    board_prefs.begin("board", true);
    board_version = board_prefs.getString("version", "NONE");
    board_prefs.end();
    if (board_version == "NONE") {
        Serial.println("No board version found");
        return;
    }
    Serial.printf("Retrieved board version: %s\n", board_version.c_str());
}