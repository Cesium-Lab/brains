#pragma once

#include <cstdint>
#include "core/isolation-layer/peripherals/spi.h"

int main(); // Implemented in main.cc

// Cesium stuff defined in board-packages
namespace Cesium {

void hal_init();

extern SpiPort Spi0;
extern SpiPort Spi1;
extern SpiPort Spi2;
extern SpiPort Spi3;
extern SpiPort Spi4;
extern SpiPort Spi5;
extern SpiPort Spi6;

namespace Pin {
extern const uint8_t BUILTIN_LED;
extern const uint8_t IMU_CS;

extern const uint8_t SPI_SCK;
extern const uint8_t SPI_MOSI;
extern const uint8_t SPI_MISO;
extern const uint8_t SPI_CS;
}

} // namespace Cesium