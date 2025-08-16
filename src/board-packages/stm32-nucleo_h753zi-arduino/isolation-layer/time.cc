#include "core/isolation-layer/time.h"

#include <Arduino.h>

void Cesium::Time::delay_us(uint32_t microseconds)
{
    delayMicroseconds(microseconds);
}

void Cesium::Time::delay(uint32_t milliseconds)
{
    ::delay(milliseconds);
}