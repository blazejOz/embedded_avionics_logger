# Embedded_Flight_Data_Recorder
[![CI](https://github.com/blazejOz/Embedded_Flight_Data_Recorder/actions/workflows/build.yaml/badge.svg)](https://github.com/blazejOz/Embedded_Flight_Data_Recorder/actions)

Embedded Flight Data Recorder (C++ / RP2350)

A  flight data recorder(aka "Black Box") built for the Raspberry Pi Pico 2(RP2350). This project captures real-time motion data from an MPU6050 IMU and logs it to an SD card using a custom C++ wrapper around the FatFs filesystem provided by carlk3 (https://github.com/carlk3/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico)

![Recorder Demo](assets/demo.gif)

## Hardware Architecture

* **Microcontroller:** Raspberry Pi Pico 2 W
* **Sensor:** MPU6050 (6-axis Gyroscope & Accelerometer)
* **Storage:** MicroSD Card Module (SPI Mode)
* **Interface:** Tactile Button & Status LEDs

### Wiring Diagram

| Component | Pin Label | Pico Pin | Function |
| :--- | :--- | :--- | :--- |
| **MPU6050** | SDA | GP4 | I2C Data |
| **MPU6050** | SCL | GP5 | I2C Clock |
| **MPU6050** | VCC | 3V3 | Power |
| **MPU6050** | GND | GND | Ground |
| | | | |
| **SD Card** | DI (MOSI)| GP19 | SPI TX |
| **SD Card** | DO (MISO)| GP16 | SPI RX |
| **SD Card** | SCK | GP18 | SPI Clock |
| **SD Card** | CS | GP17 | Chip Select |
| **SD Card** | VCC | 3V3 | Power |
| **SD Card** | GND | GND | Ground |
| | | | |
| **Control** | Button | GP13 | Start/Stop Trigger |
| **Status** | Green LED | GP14 | Ready / Recording |
| **Status** | Red LED | GP15 | Error Indicator |

## Software Design

The project uses an Object-Oriented approach to manage hardware peripherals:
* **`Recorder` Class:** Encapsulates the file system logic, handling mounting, file creation, and safe data logging.
* **`MPU6050` Class:** manages I2C communication and raw data extraction.
* **`Utils` Namespace:** button, LED and error handling.

### External Dependencies

This project utilizes the **no-OS-FatFS-SD-SDIO-SPI-RPi-Pico** library for robust SD card communication over SPI.
* **Library Author:** Carl John Kugler III
* **Source:** [https://github.com/carlk3/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico](https://github.com/carlk3/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico)

## Build Instructions

Built using the standard Raspberry Pi Pico SDK and CMake
For Nixos users use flake - nix develop

```bash
mkdir build
cd build
cmake .. 
make
```

## Roadmap / Todo

- [x] **Basic SD Card Logging** (CSV format)
- [x] **Manual Start/Stop Control** (Button + LED feedback)
- [x] **Gyroscope Data Capture** (X/Y/Z)
- [ ] **Add Accelerometer Data:** Expand MPU6050 driver to capture acceleration.
- [ ] **Timestamps:** Add millisecond precision timestamps to the log.
- [ ] **Dual Buffer:** Optimize write speeds to prevent data loss at high sample rates.
