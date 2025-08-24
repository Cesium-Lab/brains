#pragma once

#include <cstdint>

int main(); // Implemented in main.cc

// Cesium stuff defined in board-packages
namespace Cesium {

void hal_init();

namespace Pin {
extern const uint8_t BUILTIN_LED;
extern const uint8_t IMU_CS;

extern const uint8_t SPI_SCK;
extern const uint8_t SPI_MOSI;
extern const uint8_t SPI_MISO;
extern const uint8_t SPI_CS;
}

} // namespace Cesium