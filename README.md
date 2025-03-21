# Software I2C Master Library

A software-based I2C master-only implementation for Arduino and compatible microcontrollers (ESP8266, ESP32).

## Overview

This library provides a lightweight, master-only I2C driver that uses a software-based implementation to emulate the I2C protocol. It is ideal for projects that need an additional I2C bus on Arduino boards and is also compatible with ESP8266 and ESP32 microcontrollers.

## Features

- **Software-based I2C Master:** Implements the I2C protocol entirely in software without using the hardware I2C peripherals.
- **Master-only Functionality:** Supports fundamental I2C operations such as start, stop, write, and read.
- **Multi-platform Support:** Works with Arduino (AVR-based), ESP8266, and ESP32.
- **Lightweight & Easy-to-use:** Simple API with functions similar to standard I2C libraries.
- **MIT Licensed:** Free to use, modify, and distribute in your projects.

## Installation

### Manual Installation

1. Download or clone the repository.
2. Copy the `I2C.h` and `I2C.cpp` files into your Arduino libraries folder (typically `~/Documents/Arduino/libraries/`).

### Using the Arduino IDE

1. Download the repository as a ZIP file.
2. In the Arduino IDE, go to **Sketch → Include Library → Add .ZIP Library...**.
3. Select the downloaded ZIP file.

## Usage

Below is a basic example to demonstrate how to use the library:

    #include "I2C.h"

    // Define SDA and SCL pins (adjust according to your board)
    #define SDA_PIN  4
    #define SCL_PIN  5

    I2C myI2C(SDA_PIN, SCL_PIN);

    void setup() {
      // Initialize serial communication for debugging
      Serial.begin(9600);
      
      // Initialize the I2C bus
      myI2C.begin();
      
      // Begin transmission to a device at address 0x50 (example)
      if (myI2C.beginTransmission(0x50)) {
        // Write a single byte of data
        byte data = 0xAA;
        myI2C.write(data);
        // End transmission
        myI2C.endTransmission();
      }
      
      // Request 2 bytes from the device at address 0x50
      myI2C.requestFrom(0x50, 2);
      
      // Read and print received bytes
      while (myI2C.available()) {
        byte received = myI2C.read();
        Serial.println(received, HEX);
      }
    }

    void loop() {
      // Your main code here
    }

## API Reference

- **begin()**  
  Initializes the I2C bus by setting up the SDA and SCL pins.

- **beginTransmission(byte addr)**  
  Begins a transmission to the device with the specified address.

- **endTransmission()**  
  Ends the current transmission and releases the I2C bus.

- **requestFrom(byte addr, size_t len)**  
  Requests a specified number of bytes from the I2C device.

- **read()**  
  Reads a byte from the receive buffer.

- **write(byte data)**  
  Sends a single byte to the I2C device.

- **write(byte *data, size_t len)**  
  Sends multiple bytes to the I2C device.

- **available()**  
  Returns the number of bytes available to be read from the buffer.

- **flush()**  
  Clears the receive buffer.

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests on GitHub to help improve the library.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
