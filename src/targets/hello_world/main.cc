#include <Arduino.h>
#include <Wire.h>
#include "core/isolation-layer/peripherals/i2c.h"

uint32_t freq = 100'000;

const uint8_t IMU_ADDR = 0x69;

// bool initialize() {
//     return Wire.begin(SDA, SCL, freq);
// }

// bool write(uint8_t addr, uint8_t* buff, uint8_t len, bool stop = true)
// {
//     // Says to ready the TX buffer
//     Wire.beginTransmission(addr); 

//     // Fills the buffer with what I want to write 
//     Wire.write(buff, len);

//     // Send buffer (with a stop bit)
//     return (Wire.endTransmission(stop) == 0);
// }

// bool read(uint8_t addr, uint8_t reg, uint8_t* buff, uint8_t len)
// {
//     // Send address to write reg and return if not written
//      if (!write(addr, &reg, 1, false)) return false;

//     // Sends address with read, and reads [len] bytes
//     uint8_t bytes_read = Wire.requestFrom(addr, len);

//     if (bytes_read < len) return false;

//     // Read from RX buffer
//     for (int i = 0; i < len; i++)
//         buff[i] = Wire.read();

//     return true;
// }


Cesium::i2cPort port{.SDA{SDA}, .SCL{SCL}, .frequency{100'000}};

Cesium::I2C i2c{port};



void setup() {
    Serial.begin(115200);
    Serial.println("This is the 'Hello World' Target!");
    Serial.println("Setup.");
    
    // i2c.begin(SDA, SCL);
    i2c.initialize();

    // Wake up device (Bank 0, PWR_MGMT_1 = 0x06)
    i2c.write
    uint8_t reg[] = {0x06, 0x01};
    write(IMU_ADDR, reg, 2);
    // writeReg(0x06, 0x01);  
    delay(10);
    
}


void loop()
{
    // int result;

    // Wire.beginTransmission(0x69);
    // Wire.write(0x80);
    // Wire.endTransmission();
    // Wire.requestFrom(0x69, 1);
    // result = Wire.read();

    
    // Serial.print("Read" );
    // Serial.println(result, HEX);
    // Serial.println();

    uint8_t result[9]{};

    read(0x69, 0x0, result, 1);
    Serial.println(result[0], HEX);
    Serial.println();

    // writeThenRead(0x69, 0, result, 1);

    uint8_t buf[6];
    read(IMU_ADDR, 0x2D, buf, 6);

    int16_t ax = (buf[0] << 8) | buf[1];
    int16_t ay = (buf[2] << 8) | buf[3];
    int16_t az = (buf[4] << 8) | buf[5];

    Serial.print("Accel X: "); Serial.println(ax);
    Serial.print("Accel Y: "); Serial.println(ay);
    Serial.print("Accel Z: "); Serial.println(az);
    Serial.println();

    delay(500);

}