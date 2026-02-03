#pragma once
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"


// --- Utils (Button & LEDs) ---
constexpr uint START_BTN_PIN = 13;
constexpr uint GREEN_LED_PIN = 14;
constexpr uint RED_LED_PIN   = 15;

// --- SENSOR (MPU6050) ---
constexpr uint MPU_SDA_PIN = 4;
constexpr uint MPU_SCL_PIN = 5;
#define MPU_I2C_PORT i2c0

// --- SD CARD ---
constexpr uint SD_MISO_PIN = 16;
constexpr uint SD_CS_PIN   = 17;
constexpr uint SD_SCK_PIN  = 18;
constexpr uint SD_MOSI_PIN = 19;
#define SD_SPI_PORT spi0