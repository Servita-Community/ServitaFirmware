/**
 * @file version.h
 * @brief Board version information.
 * @version 0.1
 * @date 2024-07-05
*/

#ifndef VERSION_H
#define VERSION_H

#include <Arduino.h>

#define SOFTWARE_VERSION "v2.6"

extern String board_version;

void save_board_version(String version);
String get_board_version();
unsigned long hashString(const String &str);
void handle_save_brd_version(String params);


#endif  // VERSION_H