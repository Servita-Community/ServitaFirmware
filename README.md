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
    - `WebSockets` version `2.5.1`

#### Installing ESPAsyncWebServer

1. Copy this link into your browser: [ESPAsyncWebServer Version 3.0.6 ZIP](https://github.com/mathieucarbou/ESPAsyncWebServer/archive/refs/tags/v3.0.6.zip)
2. Save the ZIP file to your computer.
3. Extract the ZIP file.
4. Move the extracted folder to your Arduino libraries directory:
   - **Windows**: `C:\Users\<YourUsername>\Documents\Arduino\libraries`
   - **Linux**: `~/Arduino/libraries`

#### Installing SinricPro
1. Copy this link into your browser: [SinricPro Version 3.2.1 ZIP](https://github.com/sinricpro/esp8266-esp32-sdk/archive/refs/tags/3.2.1.zip)
2. Save the ZIP file to your computer.
3. Extract the ZIP file.
4. Move the extracted folder to your Arduino libraries directory:
   - **Windows**: `C:\Users\<YourUsername>\Documents\Arduino\libraries`
   - **Linux**: `~/Arduino/libraries`
5. Rename the folder to `SinricPro`.

#### Installing CH340 Drivers

If your ESP32 board uses the CH340 USB-to-Serial chip, you may need to install the CH340 drivers:

- **Windows**: Download and install the driver from the [official CH340 driver page](http://www.wch.cn/downloads/CH341SER_EXE.html).
- **Mac**: Download and install the driver from the [official CH340 driver page](http://www.wch.cn/downloads/CH341SER_MAC_ZIP.html).
- **Linux**: Most modern Linux distributions include the CH340 driver by default. If not, you can install it using your package manager.

#### Setting the Partition Scheme

When using the Arduino IDE to install the firmware on an ESP32 device, it is important to select the correct partition scheme to ensure that there is enough space for the application.

1. Open the Arduino IDE.
2. Go to `Tools` > `Partition Scheme`.
3. Select `Huge APP (3MB No OTA/1MB SPIFFS)` from the dropdown menu.

This partition scheme is recommended for devices with 8 MB of flash space, as it allocates a large portion of the memory for the application, ensuring that it can run without issues related to memory limitations.

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
arduino-cli lib install "WebSockets@2.5.1"
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

3. Clone the `ESPAsyncWebServer` repository and checkout the latest supported version (v3.0.6):
    ```sh
    git clone https://github.com/mathieucarbou/ESPAsyncWebServer.git
    cd ESPAsyncWebServer
    git checkout v3.0.6
    ```

#### Cloning `SinricPro`
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

3. Clone the 'SinricPro' repository and checkout the latest supported version (3.2.1):
    ```sh
    git clone https://github.com/sinricpro/esp8266-esp32-sdk.git SinricPro
    cd SinricPro
    git checkout 3.2.1
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

## Setup Instructions for Integrating Sinric Pro with Alexa and Servita

### Step 1: Create an Account on Sinric Pro
1. Visit the Sinric Pro website: [sinric.pro](https://sinric.pro)
2. Click on the "Sign Up" or "Create Account" button.
3. Fill in the required details, such as your name, email address, and password.
4. Confirm your email address by clicking on the verification link sent to your inbox.

### Step 2: Download the Sinric Pro App
1. Open the App Store (iOS) or Google Play Store (Android) on your mobile device.
2. Search for "Sinric Pro".
3. Download and install the Sinric Pro app.

### Step 3: Link Your Sinric Pro Account with Alexa
1. Open the Sinric Pro app on your mobile device.
2. Log in using the account credentials you created in Step 1.
3. Follow the in-app instructions to link your Sinric Pro account with Alexa.

### Step 4: Access the Settings Page in the Servita Web App
1. Open your web browser and navigate to the Servita web app.
2. Log in to your Servita account if prompted.

### Step 5: Log in to Sinric Pro in the Servita Integration Box
1. In the Servita web app, go to the "Settings" page.
2. Locate the Sinric Pro integration box.
3. Enter your Sinric Pro account email and password to log in and authorize the integration.

### Step 6: Add Servita as a Device in the Alexa App
1. Open the Alexa app on your mobile device.
2. If Servita has not been added automatically, go to "Devices" and tap the "+" icon to add a new device.
3. Follow the prompts to add Servita as a new device.

### Step 7: Create Routines for Your Device
1. In the Alexa app, go to the "Routines" section.
2. Tap the "+" icon to create a new routine.
3. Set up routines with the following values:
   - Routine 1: "Drink1"
   - Routine 2: "Drink2"
   - Routine 3: "Drink3"
   - Routine 4: "Cancel"
4. Configure each routine according to your preferences and save them.

### Step 8: Test Alexa with Servita
1. Use voice commands to test each routine you created.
2. Say, "Alexa, trigger [routine name]" (e.g., "Alexa, trigger Drink1").
3. Ensure that Alexa responds correctly and performs the desired action with your Servita device.

Congratulations! You have successfully set up and integrated Sinric Pro with Alexa and Servita. Enjoy your smart home automation!

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

The Servita project uses an automated release process powered by GitHub Actions. This process ensures that new firmware versions are easily distributed with minimal manual effort. When you tag a commit with a version number and push it to GitHub, the following steps are automatically executed:

1. **Version Check**: The workflow checks that the `SOFTWARE_VERSION` in the code (`version.h`) matches the version tag used for the release.
2. **Compilation**: The firmware is compiled using the latest code.
3. **Release Creation**: A GitHub release is created, and the compiled binaries are attached.

### Steps for Releasing a New Version

To release a new version, follow these steps:

1. **Update the Software Version**:
   Manually update the `SOFTWARE_VERSION` constant in `Servita/inc/version.h` to match the version you intend to release. For example, if you're releasing version `v1.1`, update the line in `version.h` like this:

   ```cpp
   #define SOFTWARE_VERSION "v1.1"
   ```

   This ensures that the version number in the code matches the release tag.

2. **Tag the Release**:
   Use the following Git commands to tag the release and push it to GitHub:

   ```bash
   git tag v1.1
   git push origin v1.1
   ```

   The tag should have a 'v' prefix followed by the version number (e.g., `v1.1`, `v2.0`). This triggers the GitHub Actions workflow to compile the code and create the release with the appropriate binaries.

### Automatic Version Update

If you forget to update the `SOFTWARE_VERSION` in `version.h` before tagging a release, the GitHub Actions workflow will automatically correct this:

- The workflow checks if the `SOFTWARE_VERSION` in `version.h` matches the version tag (e.g., `v1.1`).
- If there's a mismatch, the workflow updates the `SOFTWARE_VERSION` to match the version tag.
- A new commit with the correct version is created on the tagged release, and the old tag is replaced with the updated one.

### Important Notes

- **Version Mismatch Handling**: If the `SOFTWARE_VERSION` in the code doesn’t match the version tag, the workflow will adjust the version number and create a commit on the release tag, not on the `main` branch. This keeps the main codebase unaffected unless you decide to merge the changes manually.
  
- **Avoiding Unnecessary Commits**: By manually updating the `SOFTWARE_VERSION` in `version.h` before tagging, you prevent the workflow from creating additional commits, resulting in a cleaner release process.