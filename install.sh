#!/bin/bash

# Update package list and install dependencies
sudo apt update
sudo apt install -y curl python3-pip git

# Check if Arduino CLI is installed
if ! command -v arduino-cli &> /dev/null
then
    # Install Arduino CLI
    echo "Installing Arduino CLI..."
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
    sudo mv bin/arduino-cli /usr/local/bin/
else
    echo "Arduino CLI is already installed."
fi

# Initialize Arduino CLI configuration if it doesn't exist
if [ ! -f "$HOME/.arduino15/arduino-cli.yaml" ]; then
    echo "Configuring Arduino CLI..."
    arduino-cli config init
else
    echo "Arduino CLI configuration already exists."
fi

# Add ESP32 board support
echo "Adding ESP32 board support..."
arduino-cli core update-index
arduino-cli core install esp32:esp32@3.0.1

# Install required Python packages
echo "Installing required Python packages..."
pip3 install pyserial

# Install required libraries
echo "Installing required libraries..."
arduino-cli lib install "FastLED@3.7.0"
arduino-cli lib install "AsyncTCP@1.1.4"
arduino-cli lib install "ArduinoJson@7.0.4"

# Check if ESPAsyncWebServer is already installed
ESPASYNC_WEBSERVER_DIR="$HOME/Arduino/libraries/ESPAsyncWebServer"
if [ ! -d "$ESPASYNC_WEBSERVER_DIR" ]; then
    echo "Cloning ESPAsyncWebServer library..."
    mkdir -p "$HOME/Arduino/libraries"
    cd "$HOME/Arduino/libraries"
    git clone https://github.com/me-no-dev/ESPAsyncWebServer.git
else
    echo "ESPAsyncWebServer library is already installed."
fi

echo "Installation complete. Arduino CLI and required libraries are installed."