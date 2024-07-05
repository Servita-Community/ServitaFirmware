/**
 * @file brd_version.h
 * @brief Board version information.
 * @version 0.1
 * @date 2024-07-05
*/

#ifndef BRD_VERSION_H
#define BRD_VERSION_H

#include <Arduino.h>

extern String board_version;

void save_board_version(String version);
String get_board_version();
unsigned long hashString(const String &str);
void handle_save_brd_version(String params);


#endif  // BRD_VERSION_H