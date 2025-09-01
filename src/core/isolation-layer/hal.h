#pragma once

#include <cstdint>
#include "core/isolation-layer/peripherals/spi.h"
#include "core/isolation-layer/peripherals/i2c.h"

int main(); // Implemented in main.cc

// Cesium stuff defined in board-packages
namespace Cesium {

void hal_init();

// -------------------------
// Pins
// -------------------------

namespace Pin {
extern const uint8_t BUILTIN_LED;
extern const uint8_t IMU_CS;
}

// -------------------------
// SPI Ports
// -------------------------

// Just in case something uses it
extern SpiPort Spi0;

/*
Nucleo H753
Nucleo F042
Nucleo F303
*/
extern SpiPort Spi1;

/*
Nucleo H753
Nucleo F042 ?
Nucleo F303
*/
extern SpiPort Spi2;

/*
Nucleo H753
Nucleo F303
*/
extern SpiPort Spi3;

/*
Nucleo H753
Nucleo F303
*/
extern SpiPort Spi4;

/*
Nucleo H753
*/
extern SpiPort Spi5;

/*
Nucleo H753
*/
extern SpiPort Spi6;

// -------------------------
// i2c
// -------------------------

const uint8_t ICM20948_ADDR = 0x69;

extern i2cPort i2c1;


} // namespace Cesium