#pragma once

#include <cstdint>

int main(); // Implemented in main.cc

// Cesium stuff defined in board-packages
namespace Cesium {

void hal_init();

namespace Pin {

extern const uint8_t BUILTIN_LED;

}

} // namespace Cesium