#include "core/isolation-layer/time.h"

#include <esp32-hal.h>

void Cesium::Time::delay_us(uint32_t microseconds)
{
    delayMicroseconds(microseconds);
}

void Cesium::Time::delay(uint32_t milliseconds)
{
    ::delay(milliseconds);
}