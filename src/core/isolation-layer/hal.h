#pragma once

#include <cstdint>
#include "core/isolation-layer/peripherals/spi.h"

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

extern const uint8_t SPI_SCK;
extern const uint8_t SPI_MOSI;
extern const uint8_t SPI_MISO;
extern const uint8_t SPI_CS;
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


} // namespace Cesium