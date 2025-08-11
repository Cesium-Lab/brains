#include "core/hal.h"

int main() {
    Serial.begin(115200);
    Serial.println("This is the Playground Target");
    Serial.println("setup");
    
    while(1) {
        Serial.println("loop");
        delay(1000);
    }

    return 0;
}
