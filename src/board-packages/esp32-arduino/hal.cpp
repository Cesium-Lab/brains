#include "hal.h"
#include <Arduino.h>

void setup() {}

void loop() {main();}

void esp_delay(uint64_t microseconds) {
    delay(microseconds);
}