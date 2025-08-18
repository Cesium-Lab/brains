#pragma once

#include <cstdint>

int main();

namespace Cesium {

void hal_init();

extern const uint8_t SPI_CS;

} // namespace Cesium

// -------------------
// For pin definitions (figure out how to abstract out?)
// -------------------

// #ifdef ESP32_ARDUINO
// #include "board-packages/esp32-arduino/hal.h"
// #endif

// #ifdef ESP32_IDF
// #include "board-packages/esp32-idf/hal.h"
// #endif