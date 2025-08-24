#include "core/isolation-layer/hal.h"
#include "board-packages/esp32-arduino/hal.h" // For init

// Silencing the gods of Arduino linkage
void loop() {}
void setup() { main(); }

namespace Cesium {
    
void hal_init() {
    ::init();
}

namespace Pin {
const uint8_t BUILTIN_LED{2};
}

} // namespace Cesium