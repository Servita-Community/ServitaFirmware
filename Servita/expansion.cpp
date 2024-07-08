#include "inc/expansion.h"
#include "inc/brd_version.h"


expansion_t expansion_type = NO_EXPANSION;

void init_expansion() {
    Wire.begin();
    Wire.setClock(400000);

    Wire.beginTransmission(EXPANSION_EEPROM_ADDR);
    Wire.write(EXPANSION_CODE_BYTE_ADDR);

    if (Wire.endTransmission() != 0) {
        expansion_type = NO_EXPANSION;
        Serial.println("Expansion board eeprom not found");
        return;
    }

    Wire.requestFrom(EXPANSION_EEPROM_ADDR, 1);
    if (Wire.available()) {
        expansion_t temp = (expansion_t) Wire.read();
        if (temp == DUO_BOARD) {
            expansion_type = DUO_BOARD;
            Serial.println("Expansion board found: DUO_BOARD");
            return;
        }
    }

    Serial.println("Expansion board found, but unknown type");
    expansion_type = BOARD_UNKNOWN;
    return;
}

expansion_t get_expansion_version() {
    switch (expansion_type) {
        case NO_EXPANSION:
            Serial.println("No expansion board found");
            break;
        case BOARD_UNKNOWN:
            Serial.println("Expansion board found, but unknown type");
            break;
        case DUO_BOARD:
            Serial.println("Expansion board found: DUO_BOARD");
            break;
    }
    return expansion_type;
}

void save_expansion_type(expansion_t type) {
    Wire.beginTransmission(EXPANSION_EEPROM_ADDR);
    Wire.write(EXPANSION_CODE_BYTE_ADDR);
    Wire.write((uint8_t) type);
    Wire.endTransmission();

    // Verify the value was saved correctly
    Wire.requestFrom(EXPANSION_EEPROM_ADDR, 1);
    if (Wire.available()) {
        expansion_t temp = (expansion_t) Wire.read();
        if (temp == type) {
            Serial.printf("Saved expansion type: 0x%x\n", type);
            return;
        }
    }   

    Serial.println("Failed to save expansion type");
}

void handle_save_expansion_type(String params) {
    int firstSpaceIndex = params.indexOf(' ');
    String password;
    String hex_code;

    if (firstSpaceIndex != -1) {
        password = params.substring(0, firstSpaceIndex);
        hex_code = params.substring(firstSpaceIndex + 1);
    } else {
        password = params;
        hex_code = "";
    }

    if (hashString(password) == 300951455) {
        long type_value = strtol(hex_code.c_str(), NULL, 16); // Convert hex string to integer
        if (type_value >= 0 && type_value <= 255) {  // Ensure the value is within the uint8_t range
            expansion_t type = (expansion_t) type_value;
            save_expansion_type(type);
        } else {
            Serial.println("Invalid expansion type value");
        }
    } else {
        Serial.println("Invalid password");
    }
}
