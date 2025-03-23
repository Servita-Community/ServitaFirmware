#!/bin/bash

# Get optional USB number argument, default to 0
USB_NUM=${1:-0}
PORT="/dev/ttyUSB${USB_NUM}"

# Run python3 export_html.py
python3 export_html.py
if [ $? -ne 0 ]; then
  echo "python3 export_html.py failed"
  exit 1
fi

# Compile with arduino-cli
arduino-cli compile --fqbn esp32:esp32:esp32:PartitionScheme=huge_app Servita
if [ $? -ne 0 ]; then
  echo "arduino-cli compile failed"
  exit 1
fi

# Upload with arduino-cli
arduino-cli upload -p "$PORT" --fqbn esp32:esp32:esp32:PartitionScheme=huge_app Servita
if [ $? -ne 0 ]; then
  echo "arduino-cli upload failed on $PORT"
  exit 1
fi

# Monitor with arduino-cli
arduino-cli monitor -p "$PORT" -b esp32:esp32:esp32:PartitionScheme=huge_app -c baudrate=115200
if [ $? -ne 0 ]; then
  echo "arduino-cli monitor failed on $PORT"
  exit 1
fi