#include "core/isolation-layer/hal.h"

#include <board.h> // init()
#include <pins_arduino_analog.h> // PB3

namespace Cesium {
    
void hal_init() {
    ::init(); // NEEDS this! (for the onboard timer I think)
}

namespace Pin {

const uint8_t BUILTIN_LED{PB3};

}

} // namespace Cesium