# Servita Project

## Overview

The Servita project is an embedded system firmware designed for the ESP32 platform. It includes a web interface for controlling and monitoring the device. The project has been refactored to improve readability and maintainability by separating the HTML content into distinct files that can be easily edited and tested independently of the firmware.

## Repository Structure

```
ServitaFirmware_InternalTeamOnly/
├── export_html.py
├── html/
│   └── main.html
├── install.sh
├── README.md
└── Servita/
    ├── button.cpp
    ├── inc/
    │   ├── button.h
    │   ├── led.h
    │   ├── main_html.h
    │   ├── motor.h
    │   ├── pour.h
    │   ├── serial_cmd.h
    │   └── server.h
    ├── led.cpp
    ├── motor.cpp
    ├── pour.cpp
    ├── serial_cmd.cpp
    ├── server.cpp
    └── Servita.ino
```

### `html` Directory

Contains the HTML file for the main application interface:
- `main.html`: The HTML content for the main application interface.

### `Servita` Directory

Contains the main firmware code and the exported HTML header files:
- `inc/`: Directory for header files.
  - `button.h`: The header file for button-related functions and definitions.
  - `led.h`: The header file for LED-related functions and definitions.
  - `main_html.h`: The header file containing the HTML content for the main application interface.
  - `motor.h`: The header file for motor-related functions and definitions.
  - `pour.h`: The header file for pour-related functions and definitions.
  - `serial_cmd.h`: The header file for serial command-related functions and definitions.
  - `server.h`: The header file for server-related functions and definitions.
- `button.cpp`: The source file for button-related functions.
- `led.cpp`: The source file for LED-related functions.
- `motor.cpp`: The source file for motor-related functions.
- `pour.cpp`: The source file for pour-related functions.
- `serial_cmd.cpp`: The source file for serial command-related functions.
- `server.cpp`: The source file for server-related functions.
- `Servita.ino`: The main Arduino sketch file.

### `export_html.py`

A Python script that converts the HTML files in the `html` directory into C header files for inclusion in the Arduino project. This script should be run whenever changes are made to the HTML files to ensure the firmware is up-to-date with the latest HTML content.

### `install.sh`

A shell script for installing dependencies and setting up the project.

## Running the Export Script

To update the header files with the latest HTML content, simply run the following command from the root directory:

```sh
python3 export_html.py
```

This will generate the `main_html.h` file in the `Servita/inc` directory.

## Advantages of Exporting HTML Files

1. **Readability**: By maintaining the HTML content in separate files, it becomes much easier to read and edit. This improves the overall readability of the codebase.
   
2. **Local Testing**: The HTML files can be opened directly in a web browser for local testing and debugging. This allows developers to verify the appearance and functionality of the web interface without needing to upload the firmware to the ESP32.

3. **Separation of Concerns**: Keeping the HTML, CSS, and JavaScript separate from the C++ code enhances modularity. In the future, maintaining separate CSS and JavaScript files would further improve this separation, making the project easier to maintain and extend.

## Installation and Setup

### Using Arduino IDE

#### Adding ESP32 Board Package

1. Open the Arduino IDE.
2. Go to `File` > `Preferences`.
3. In the "Additional Boards Manager URLs" field, add the following URL:
    ```
    https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
    ```
4. Click `OK` to close the Preferences window.
5. Go to `Tools` > `Board` > `Boards Manager`.
6. Search for `esp32` and install the `esp32` by Espressif Systems version `3.0.1`.
7. Select the ESP32 Dev Module board from the list: `Tools` > `Board` > `ESP32 Arduino` > `ESP32 Dev Module`.

#### Installing Required Libraries

1. Open the Arduino IDE.
2. Go to `Tools` > `Manage Libraries`.
3. In the Library Manager, search for and install the following libraries:
   - `FastLED` version `3.7.0`
   - `AsyncTCP` version `1.1.4`
   - `ArduinoJson` version `7.0.4`

#### Installing ESPAsyncWebServer

1. Copy this link into your browser: [ESPAsyncWebServer Version 3.0.6 ZIP](https://github.com/mathieucarbou/ESPAsyncWebServer/archive/refs/tags/v3.0.6.zip)
2. Save the ZIP file to your computer.
3. Extract the ZIP file.
4. Move the extracted folder to your Arduino libraries directory:
   - **Windows**: `C:\Users\<YourUsername>\Documents\Arduino\libraries`
   - **Linux**: `~/Arduino/libraries`

#### Installing CH340 Drivers

If your ESP32 board uses the CH340 USB-to-Serial chip, you may need to install the CH340 drivers:

- **Windows**: Download and install the driver from the [official CH340 driver page](http://www.wch.cn/downloads/CH341SER_EXE.html).
- **Mac**: Download and install the driver from the [official CH340 driver page](http://www.wch.cn/downloads/CH341SER_MAC_ZIP.html).
- **Linux**: Most modern Linux distributions include the CH340 driver by default. If not, you can install it using your package manager.

### Using Arduino CLI

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

4. Install the required Python packages:
    ```sh
    pip install pyserial
    ```

5. Install Git if it's not already installed:
    ```sh
    sudo apt-get install git
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

5. Install the required Python packages:
    ```sh
    pip install pyserial
    ```

6. Install Git if it's not already installed:
    Download and install Git from the [official Git website](https://git-scm.com/).

#### Mac

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

4. Install the required Python packages:
    ```sh
    pip install pyserial
    ```

5. Install Git if it's not already installed:
    ```sh
    brew install git
    ```

### Install Required Libraries

#### Using Arduino CLI

```sh
arduino-cli lib install "FastLED@3.7.0"
arduino-cli lib install "AsyncTCP@1.1.4"
arduino-cli lib install "ArduinoJson@7.0.4"
```

#### Cloning `ESPAsyncWebServer`

Instead of using the version of `ESPAsyncWebServer` that the Arduino CLI automatically installs, clone the repository directly:

1. Navigate to your Arduino libraries folder. The default locations are:
    - **Linux**: `~/Arduino/libraries`
    - **Windows**: `C:\Users\<YourUsername>\Documents\Arduino\libraries`
    - **Mac**: `~/Documents/Arduino/libraries`

2. Open a terminal (or command prompt) and navigate to the Arduino libraries folder:
    ```sh
    cd ~/Arduino/libraries
    # or for Windows
    cd C:\Users\<YourUsername>\Documents\Arduino\libraries
    ```

3. Clone the `ESPAsyncWebServer` repository:
    ```sh
    git clone https://github.com/mathieucarbou/ESPAsyncWebServer.git
    ```

4. Checkout the latest supported version (v3.0.6):
    ```sh
    cd ESPAsyncWebServer
    git checkout v3.0.6
    ```

### Compilation and Upload

#### Compiling with Arduino CLI

To compile the firmware using the Arduino CLI, use the following command:

```sh
arduino-cli compile --fqbn esp32:esp32:esp32 Servita
```

#### Uploading to ESP32

To upload the compiled firmware to the ESP32, use the following command, replacing `/dev/ttyUSB0` (or the appropriate serial port for your ESP32 device):

```sh
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32 Servita
```

#### Monitoring Serial Output

To monitor the serial output of the ESP32, use the following command:

```sh
arduino-cli monitor -p /dev/ttyUSB0 -b esp32:esp32:esp32 -c baudrate=115200
```

### Using `manufacturing.py`

#### Prerequisites

1. Install the `arduino-cli` tool for your operating system.

2. Download the desired firmware version from the [ServitaFirmware releases](https://github.com/Servita-Community/ServitaFirmware/releases).

3. Place the release files into a folder named `build` in the root of the Servita firmware repository.

#### Run

Run the following command:

```sh
python manufacturing.py --port USB_PORT
```

Replace `USB_PORT` with the actual USB port where the device is connected.

#### Output Colors

The script will provide output as it goes through various stages. The final output color indicates the configuration status of the device:

| Color   | Description                                                                 |
|---------|-----------------------------------------------------------------------------|
| Cyan    | Both the ESP32 and the expansion board have been successfully configured.   |
| Yellow  | Only the ESP32 main board has been configured.                              |
| Red     | Neither the main board nor the expansion board were configured properly.    |

If you follow these steps and the output colors, you can easily determine the success of the configuration process.

## Automating Releases

To automate the process of creating a release, you can use GitHub Actions. By tagging a specific commit and pushing to GitHub, a release will be automatically created. To create a release, tag a commit with a version number and push it to GitHub. For example:

```
git tag v1.0
git push origin v1.0
```

This will trigger the GitHub Actions workflow, compile the code, and create a release with the compiled binaries attached.  All versions should be tagged with a 'v' prefix followed by the version number (e.g., `v1.0`, `v1.1`, etc.). The automated release process ensures that new versions of the firmware are easily distributed and reduces the manual effort involved in creating releases.