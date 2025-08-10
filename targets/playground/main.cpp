#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    Serial.println("This is the \"Playground\" Target");
}

void loop() {
    Serial.println("wow");
    delay(1000);
}