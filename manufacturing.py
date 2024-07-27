import argparse
import subprocess
import serial
import time
import os
import sys



# Global Variables
PORT = "/dev/ttyUSB0"

# Constants
BAUDRATE = 115200
FQBN = 'esp32:esp32:esp32'

# Function to flash the board
def flash_board():
    FLASH_COMMAND = ['arduino-cli', 'upload', '-p', PORT, '--fqbn', FQBN, '--input-dir', './build', '--verify']
    result = subprocess.run(FLASH_COMMAND)
    return result.returncode == 0

# Function to monitor the serial output and send commands
def monitor_serial():
    with serial.Serial(PORT, BAUDRATE, timeout=1) as ser:
        result_str = ""

        time.sleep(1)
        initial_response = ser.read_all().decode()
        print("Initial response:")
        print(initial_response)

        ser.write(b'restart\n')
        print("\n\nSent: restart")
        time.sleep(3)

        response = ser.read_all().decode()
        print(response)

        ser.write(b'saveBrdVersion obarim v1.0\n')
        print("\n\nSent: saveBrdVersion obarim v1.0")
        time.sleep(1)
        response = ser.read_all().decode()
        result_str += response
        print(response)

        ser.write(b'saveExpansionType obarim 0x10\n')
        print("\n\nSent: saveExpansionType obarim 0x10")
        time.sleep(1)
        response = ser.read_all().decode()
        result_str += response

        print(response)

        if "Saved board version: v1.0" in result_str and "Saved expansion type: 0x10" in result_str:
            ser.write(b'setBoardLed 0x00FFFF\n')
            print("\n\nSent: setBoardLed 0x00FFFF")
        elif "Saved board version: v1.0" in result_str:
            ser.write(b'setBoardLed 0xFFFF00\n')
            print("\n\nSent: setBoardLed 0xFFFF00")
        else:
            ser.write(b'setBoardLed 0xFF0000\n')
            print("\n\nSent: setBoardLed 0xFF0000")

# Main function
def main():
    global PORT
    
    parser = argparse.ArgumentParser(description='Serial port communication script.')
    parser.add_argument('--port', type=str, help='COM port to use. E.g., COM3 on Windows or /dev/ttyUSB0 on Linux.', default=None)

    args = parser.parse_args()

    if args.port is not None:
        PORT = args.port

    
    if not flash_board():
        print("arduino-cli upload failed")
        return

    try:
        monitor_serial()
    except Exception as e:
        print(f"Error during serial monitoring: {e}")

if __name__ == "__main__":
    main()