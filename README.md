# Servita Project

## Overview

The Servita project is an embedded system firmware designed for the ESP32 platform. It includes a web interface for controlling and monitoring the device. The project has been refactored to improve readability and maintainability by separating the HTML content into distinct files that can be easily edited and tested independently of the firmware.

## Repository Structure

```
ServitaFirmware_InternalTeamOnly/
├── export_html.py
├── html/
│   ├── captive.html
│   └── main.html
├── README.md
└── Servita/
    ├── inc/
    │   ├── captive_html.h
    │   ├── main_html.h
    │   └── motor.h
    ├── Servita.ino
    ├── motor.cpp
```

### `html` Directory

Contains the HTML files for the main and captive portals:
- `captive.html`: The HTML content for the captive portal.
- `main.html`: The HTML content for the main application interface.

### `Servita` Directory

Contains the main firmware code and the exported HTML header files:
- `inc/`: Directory for header files.
  - `captive_html.h`: The header file containing the HTML content for the captive portal.
  - `main_html.h`: The header file containing the HTML content for the main application interface.
  - `motor.h`: The header file for motor-related functions and definitions.
- `motor.cpp`: The source file for motor-related functions.
- `Servita.ino`: The main Arduino sketch file.

### `export_html.py`

A Python script that converts the HTML files in the `html` directory into C header files for inclusion in the Arduino project. This script should be run whenever changes are made to the HTML files to ensure the firmware is up-to-date with the latest HTML content.

## Running the Export Script

To update the header files with the latest HTML content, simply run the following command from the root directory:

```sh
python3 export_html.py
```

This will generate the `captive_html.h` and `main_html.h` files in the `Servita/inc` directory.

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

## Installation and Setup

### Install Arduino CLI

#### Linux

1. Download and install the Arduino CLI:
    ```sh
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
    sudo mv bin/arduino-cli /usr/local/bin/
    ```

2. Configure the Arduino CLI:
    ```sh
    arduino-cli config init
    ```

3. Add the ESP32 board support:
    ```sh
    arduino-cli core update-index
    arduino-cli core install esp32:esp32@3.0.1
    ```

4. Install the required python packages:
    ```sh
    pip install pyserial
    ```

#### Windows

1. Download the Arduino CLI executable from the [Arduino CLI GitHub releases page](https://github.com/arduino/arduino-cli/releases).

2. Extract the executable and add it to your system PATH.

3. Configure the Arduino CLI:
    ```sh
    arduino-cli config init
    ```

4. Add the ESP32 board support:
    ```sh
    arduino-cli core update-index
    arduino-cli core install esp32:esp32@3.0.1
    ```

### Install Required Libraries

```sh
arduino-cli lib install "FastLED@3.7.0"
arduino-cli lib install "AsyncTCP@1.1.4"
arduino-cli lib install "ESP Async WebServer@2.10.5"
```

### Compilation and Upload

#### Compiling with Arduino CLI

To compile the firmware using the Arduino CLI, use the following command:

```sh
arduino-cli compile --fqbn esp32:esp32:esp32 Servita
```

#### Uploading to ESP32

To upload the compiled firmware to the ESP32, use the following command, replacing `/dev/ttyUSB0` with the appropriate serial port for your ESP32 device:

```sh
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32 Servita
```

## Conclusion

This refactor improves the Servita project's structure, making it easier to manage and extend. By separating the HTML content and allowing for local testing, developers can more efficiently develop and maintain the web interface for the ESP32 firmware. Future enhancements will continue to focus on modularity and maintainability, with an emphasis on separating CSS and JavaScript files.