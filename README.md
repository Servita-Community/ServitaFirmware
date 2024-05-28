# Servita Project

## Overview

The Servita project is an embedded system firmware designed for the ESP32 platform. It includes a web interface for controlling and monitoring the device. The project has been refactored to improve readability and maintainability by separating the HTML content into distinct files that can be easily edited and tested independently of the firmware.

## Repository Structure

```
ServitaFirmware_InternalTeamOnly/
├── export_html.py
├── html/
│   ├── captive.html
│   ├── main.html
├── README.md
└── Servita/
    ├── captive_html.h
    ├── main_html.h
    └── Servita.ino
```

### `html` Directory

Contains the HTML files for the main and captive portals:
- `captive.html`: The HTML content for the captive portal.
- `main.html`: The HTML content for the main application interface.

### `Servita` Directory

Contains the main firmware code and the exported HTML header files:
- `captive_html.h`: The header file containing the HTML content for the captive portal.
- `main_html.h`: The header file containing the HTML content for the main application interface.
- `Servita.ino`: The main Arduino sketch file.

### `export_html.py`

A Python script that converts the HTML files in the `html` directory into C header files for inclusion in the Arduino project. This script should be run whenever changes are made to the HTML files to ensure the firmware is up-to-date with the latest HTML content.

## Running the Export Script

To update the header files with the latest HTML content, simply run the following command from the root directory:

```sh
python3 export_html.py
```

This will generate the `captive_html.h` and `main_html.h` files in the `Servita` directory.

## Advantages of Exporting HTML Files

1. **Readability**: By maintaining the HTML content in separate files, it becomes much easier to read and edit. This improves the overall readability of the codebase.
   
2. **Local Testing**: The HTML files can be opened directly in a web browser for local testing and debugging. This allows developers to verify the appearance and functionality of the web interface without needing to upload the firmware to the ESP32.

3. **Separation of Concerns**: Keeping the HTML, CSS, and JavaScript separate from the C++ code enhances modularity. In the future, maintaining separate CSS and JavaScript files would further improve this separation, making the project easier to maintain and extend.

## Future Work

### Separate CSS and JavaScript Files

To further improve the maintainability and readability of the project, future updates should consider:
- Moving CSS to separate `.css` files.
- Moving JavaScript to separate `.js` files.

These files can then be referenced in the HTML, allowing for easier updates and testing of the styles and scripts independently of the HTML content.

## Compilation and Upload

### Compiling with Arduino CLI

To compile the firmware using the Arduino CLI, use the following command:

```sh
arduino-cli compile --fqbn esp32:esp32:esp32 Servita
```

### Uploading to ESP32

To upload the compiled firmware to the ESP32, use the following command, replacing `/dev/ttyUSB0` with the appropriate serial port for your ESP32 device:

```sh
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32 Servita
```

## Conclusion

This refactor improves the Servita project's structure, making it easier to manage and extend. By separating the HTML content and allowing for local testing, developers can more efficiently develop and maintain the web interface for the ESP32 firmware. Future enhancements will continue to focus on modularity and maintainability, with an emphasis on separating CSS and JavaScript files.