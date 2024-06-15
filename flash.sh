#!/bin/bash

# Run python3 export_html.py
python3 export_html.py
if [ $? -ne 0 ]; then
  echo "python3 export_html.py failed"
  exit 1
fi

# Compile with arduino-cli
arduino-cli compile --fqbn esp32:esp32:esp32 Servita
if [ $? -ne 0 ]; then
  echo "arduino-cli compile failed"
  exit 1
fi

# Upload with arduino-cli
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32 Servita
if [ $? -ne 0 ]; then
  echo "arduino-cli upload failed"
  exit 1
fi

# Monitor with arduino-cli
arduino-cli monitor -p /dev/ttyUSB0 -b esp32:esp32:esp32 -c baudrate=115200
if [ $? -ne 0 ]; then
  echo "arduino-cli monitor failed"
  exit 1
fi