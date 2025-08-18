#pragma once

namespace Cesium {

void hal_init();

} // namespace Cesium

#ifdef ESP32_ARDUINO
#include "board-packages/esp32-arduino/hal.h"
#endif

// #ifdef ESP32_IDF
// #include "board-packages/esp32-idf/hal.h"
// #endif