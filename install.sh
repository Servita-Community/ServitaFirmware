#!/bin/bash

# Update package list and install dependencies
sudo apt update
sudo apt install -y curl

# Install Arduino CLI
echo "Installing Arduino CLI..."
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
sudo mv bin/arduino-cli /usr/local/bin/

# Initialize Arduino CLI configuration
echo "Configuring Arduino CLI..."
arduino-cli config init

# Add ESP32 board support
echo "Adding ESP32 board support..."
arduino-cli core update-index
arduino-cli core install esp32:esp32@2.0.16

# Install required libraries
echo "Installing required libraries..."
arduino-cli lib install "FastLED@3.7.0"
arduino-cli lib install "WiFi@2.0.0"
arduino-cli lib install "AsyncTCP@1.1.4"
arduino-cli lib install "ESP Async WebServer@2.10.0"
arduino-cli lib install "FS@2.0.0"
arduino-cli lib install "DNSServer@2.0.0"
arduino-cli lib install "Preferences@2.0.0"

echo "Installation complete. Arduino CLI and required libraries are installed."