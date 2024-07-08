import subprocess
import serial
import time

# Constants
PORT = '/dev/ttyUSB0'
BAUDRATE = 115200
FQBN = 'esp32:esp32:esp32'
FLASH_COMMAND = ['arduino-cli', 'upload', '-p', PORT, '--fqbn', FQBN, '--input-dir', './build', '--verify']
MONITOR_COMMAND = ['arduino-cli', 'monitor', '-p', PORT, '-b', FQBN, '-c', f'baudrate={BAUDRATE}']

# Function to flash the board
def flash_board():
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
    if not flash_board():
        print("arduino-cli upload failed")
        return

    try:
        monitor_serial()
    except Exception as e:
        print(f"Error during serial monitoring: {e}")

if __name__ == "__main__":
    main()