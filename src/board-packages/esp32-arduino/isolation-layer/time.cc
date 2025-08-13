#include "core/isolation-layer/time.h"

#include <Arduino.h>

void Cesium::Time::delay(uint64_t microseconds)
{
    delayMicroseconds(microseconds);
}