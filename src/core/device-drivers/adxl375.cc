#include "core/device-drivers/adxl375.h"
#include "core/utilities/bits.h"
#include "core/isolation-layer/time.h"
#include <Arduino.h>
#include <cstring> // memset

namespace Cesium::Sensor {

extern float gravity; // m/s2 TODO: FIX THIS IS A BANDAID

Adxl375::Adxl375(Spi spi, uint8_t cs_pin) 
    : _spi{spi}, _cs_pin{cs_pin} {
    Gpio::init_digital(_cs_pin, GpioType::DIGITAL_OUT);
    Gpio::write_digital(_cs_pin, true);
}

void Adxl375::initialize() {
    // Enables measurement mode
    // _write_single(REG_POWER_CTL, 0x00); // standby
    // _write_single(REG_BW_RATE, 0x0D);   // 800 Hz
    // _write_single(REG_DATA_FORMAT, 0x00); // right-justified, full-res
    _write_single(REG_POWER_CTL, 0x08); // Enable measurement
    // Time::delay(5);           // > 1 ODR period
    // uint8_t junk[6];
    // _read_burst(REG_DATAX0, junk, 6); // throw away first frame

    // _write_single(REG_POWER_CTL, 0x00); // standby
    // Time::delay(10);

    // _write_single(REG_DATA_FORMAT, 0x00);
    // _write_single(REG_BW_RATE, 0x0A);   // 100 Hz (slow but safe)

    // _write_single(REG_POWER_CTL, 0x08); // RESET bit
    // Time::delay(10);

    // _write_single(REG_POWER_CTL, 0x04); // measure
    // Time::delay(20);
}


uint8_t Adxl375::chip_id() {
    return _read_single(REG_WHO_AM_I);
}

adxl375_data_t Adxl375::read()
{

    adxl375_data_t result;
    uint8_t buffer[6]{};

    _read_burst(REG_DATAX0, buffer, 6);

    // Serial3.println(buffer[0]);
    // Serial3.println(buffer[1]);
    // Serial3.println(buffer[2]);
    // Serial3.println(buffer[3]);
    // Serial3.println(buffer[4]);
    // Serial3.println(buffer[5]);
    // Using this 
    result.accel_x = bytes_to_16(buffer[1], buffer[0]) * LSB_TO_G * gravity;
    result.accel_y = bytes_to_16(buffer[3], buffer[2]) * LSB_TO_G * gravity;
    result.accel_z = bytes_to_16(buffer[5], buffer[4]) * LSB_TO_G * gravity;

    return result;
}


//////////////////////////////////////////////////
//              Read
//////////////////////////////////////////////////

uint8_t Adxl375::_read_single(uint8_t reg) {

    uint8_t tx[2] = {(uint8_t)(reg | 0x80), 0x00};
    uint8_t rx[2] = {};

    Gpio::write_digital(_cs_pin, false);
    _spi.begin_transaction();

    _spi.transfer(tx, rx, 2); // read mask

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, true);

    return rx[1];
}


void Adxl375::_read_burst(uint8_t reg, uint8_t* rx_buf, uint8_t len) {

    // uint8_t tx[len + 1] = {};
    _tx[0] = reg | 0xC0;
    memset(_tx + 1, 0x00, len);
    
    // uint8_t rx[len + 1] = {};

    Gpio::write_digital(_cs_pin, false);
    _spi.begin_transaction();

    _spi.transfer(_tx, _rx, len+1); // read mask

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, true);

    memcpy(rx_buf, _rx + 1, len);

}

//////////////////////////////////////////////////
//              Write
//////////////////////////////////////////////////


uint8_t Adxl375::_write_single(uint8_t reg, uint8_t val) {

    uint8_t tx_buf[1] = {val};
 
    _write_burst(reg, tx_buf, 1);

    return 1;
}


void Adxl375::_write_burst(uint8_t reg, const uint8_t* tx_buf, uint8_t len) {

    // uint8_t tx[len + 1] = {};
    _tx[0] = reg & 0x7F;
    memcpy(_tx + 1, tx_buf, len);
    
    // uint8_t rx[len + 1] = {};

    Gpio::write_digital(_cs_pin, false);
    _spi.begin_transaction();

    _spi.transfer(_tx, _rx, len+1); // read mask

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, true);
}


} // namespace Cesium::Sensor