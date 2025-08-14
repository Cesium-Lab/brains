#pragma once

#include <stdint.h>

namespace Cesium::Time {

void delay_us(uint32_t microseconds);
void delay(uint32_t milliseconds);

} // namespace Cesium::Time