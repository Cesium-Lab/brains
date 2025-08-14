#include <Arduino.h>

const uint8_t LED_PIN{13};

void setup() {
    Serial.begin(115200);
    Serial.println("This is the 'Hello World' Target!");

    Serial.println("Setup.");
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    Serial.println("Loop");
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
}
