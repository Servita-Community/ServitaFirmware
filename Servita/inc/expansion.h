#ifndef EXPANSION_H
#define EXPANSION_H

#include <Wire.h>
#include "inc/pins.h"

#define EXPANSION_EEPROM_ADDR 0x50
#define EXPANSION_CODE_BYTE_ADDR 0xFF

typedef enum {
    NO_EXPANSION=0x00,
    BOARD_UNKNOWN=0x01,
    DUO_BOARD=0x10,
} expansion_t;

extern expansion_t expansion_type;

void init_expansion();
expansion_t get_expansion_version();
void save_expansion_type(expansion_t type);
void handle_save_expansion_type(String params);


#endif // EXPANSION_H