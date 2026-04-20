// #include <ArduinoEigen/Eigen/Core>
#include "core/isolation-layer/math/Eigen.h"
#include <Arduino.h>
// #include <SPI.h>
// #include "core/isolation-layer/peripherals/spi.h"
// #include <Adafruit_ICM20948.h>

const uint8_t LED_PIN{2};

const uint8_t VSPI_SCK{18};
const uint8_t VSPI_MOSI{23};
const uint8_t VSPI_MISO{19};
const uint8_t IMU_CS{5};

// Adafruit_ICM20948 dev;

// SPISettings settings;

void setup() {
    Serial.begin(115200);
    Serial.println("This is the 'Hello World' Target!");
    Serial.println("Setup.");

    Cesium::Vector3f vec;

    
}

void loop() {
    
}



// pinMode(LED_PIN, OUTPUT);
//     pinMode(IMU_CS, OUTPUT);
//     digitalWrite(IMU_CS, HIGH);

//     SPI.begin(VSPI_SCK, VSPI_MISO, VSPI_MOSI);

//     // if (dev.begin_SPI(IMU_CS, VSPI_SCK, VSPI_MISO, VSPI_MOSI)) {
//     //     Serial.println("Failed to find ICM20948 chip");
//         // while (1) {
//         //     delay(10);
//         // }
//     // }
//     dev.begin_SPI(IMU_CS, VSPI_SCK, VSPI_MISO, VSPI_MOSI);

    // delay(2000);
    // dev.configureI2CMaster();
    // delay(2000);
    // dev.enableI2CMaster(true);
    // delay(2000);





// Serial.println("Loop");
// digitalWrite(LED_PIN, HIGH);
// delay(500);
// digitalWrite(LED_PIN, LOW);
// delay(500);

// uint8_t buffer[] = {0,0};

// digitalWrite(IMU_CS, LOW);
// SPI.beginTransaction(settings);
// SPI.transfer(0b10000000);
// uint8_t result = SPI.transfer(0);
// SPI.endTransaction();
// digitalWrite(IMU_CS, HIGH);

// Serial.println(result, HEX);
// sensors_event_t accel;
// sensors_event_t gyro;
// sensors_event_t mag;
// sensors_event_t temp;
// dev.getEvent(&accel, &gyro, &temp, &mag);

// Serial.print("\t\tTemperature ");
// Serial.print(temp.temperature);
// Serial.println(" deg C");

// /* Display the results (acceleration is measured in m/s^2) */
// Serial.print("\t\tAccel X: ");
// Serial.print(accel.acceleration.x);
// Serial.print(" \tY: ");
// Serial.print(accel.acceleration.y);
// Serial.print(" \tZ: ");
// Serial.print(accel.acceleration.z);
// Serial.println(" m/s^2 ");

// Serial.print("\t\tMag X: ");
// Serial.print(mag.magnetic.x);
// Serial.print(" \tY: ");
// Serial.print(mag.magnetic.y);
// Serial.print(" \tZ: ");
// Serial.print(mag.magnetic.z);
// Serial.println(" uT");

// /* Display the results (acceleration is measured in m/s^2) */
// Serial.print("\t\tGyro X: ");
// Serial.print(gyro.gyro.x);
// Serial.print(" \tY: ");
// Serial.print(gyro.gyro.y);
// Serial.print(" \tZ: ");
// Serial.print(gyro.gyro.z);
// Serial.println(" radians/s ");
// Serial.println();