#include "core/isolation-layer/time.h"

#include <thread>   // Required for std::this_thread::sleep_for
#include <chrono>   // Required for std::chrono::seconds, milliseconds, etc.

void Cesium::Time::delay(uint64_t microseconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
}