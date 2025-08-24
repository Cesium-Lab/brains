#include "core/isolation-layer/hal.h"
#include <Arduino.h>
// Silencing the gods of Arduino linkage
void loop() {}
void setup() { main(); }

namespace Cesium {
    
void hal_init() {
    ::init();
    // Just in case
}

namespace Pin {
const uint8_t BUILTIN_LED{2}; // Should be LED_BUILTIN from Arduino but not sure which header
}

} // namespace Cesium