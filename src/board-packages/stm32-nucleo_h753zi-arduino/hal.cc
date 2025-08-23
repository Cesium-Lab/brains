#include "core/isolation-layer/hal.h"
#include <Arduino.h>

namespace Cesium {
    
void hal_init() {
    ::init();
}

} // namespace Cesium