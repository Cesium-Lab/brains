#include "core/device-drivers/lis2mdl.h"
#include "core/isolation-layer/time.h"
#include "core/utilities/bits.h"
// #include <Arduino.h>
#include <cstring> // memset

namespace Cesium::Sensor {



Lis2Mdl::Lis2Mdl(Spi spi, uint8_t cs_pin) 
    : _spi{spi}, _cs_pin{cs_pin} {
    Gpio::init_digital(_cs_pin, GpioType::DIGITAL_OUT);
    Gpio::write_digital(_cs_pin, true);
}

void Lis2Mdl::initialize() {
    _write_single(CFG_REG_A, 0b00100000); // soft reset = 1
    Time::delay(10);

    _write_single(CFG_REG_C, 0b00110100); // Disable I2C, enable BDU, enable 4-wire SPI (by default is only 3-wire)
    _write_single(CFG_REG_A, 0b10001100); // Temperature compensation, 100 Hz, continuous operation

}

uint8_t Lis2Mdl::chip_id() {
    return _read_single(REG_WHO_AM_I);
}

lis2mdl_data_t Lis2Mdl::read()
{

    lis2mdl_data_t result;
    uint8_t buffer[8]{};

    _read_burst(REG_OUTX_L_REG, buffer, 6);

    // Using this 
    result.B_field_uT[0] = bytes_to_float(buffer[1], buffer[0]) * MAG_LSB_TO_MGAUSS * MGAUSS_TO_uT;
    result.B_field_uT[1] = bytes_to_float(buffer[3], buffer[2]) * MAG_LSB_TO_MGAUSS * MGAUSS_TO_uT;
    result.B_field_uT[2] = bytes_to_float(buffer[5], buffer[4]) * MAG_LSB_TO_MGAUSS * MGAUSS_TO_uT;
    // result.temp = bytes_to_float(buffer[7], buffer[6]) / TEMP_DEG_C_TO_LSB; // TODO

    return result;
}


//////////////////////////////////////////////////
//              Read
//////////////////////////////////////////////////

uint8_t Lis2Mdl::_read_single(uint8_t reg) {

    // uint8_t tx[2] = {(uint8_t)(reg | 0x80), 0x00};
    _tx[0] = reg | 0x80;
    // uint8_t rx[2] = {};

    Gpio::write_digital(_cs_pin, false);
    _spi.begin_transaction();

    _spi.transfer(_tx, _rx, 2); // read mask

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, true);

    return _rx[1];
}


void Lis2Mdl::_read_burst(uint8_t reg, uint8_t* rx_buf, uint8_t len) {

    // uint8_t tx[len + 1] = {};
    _tx[0] = reg | 0x80;
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


uint8_t Lis2Mdl::_write_single(uint8_t reg, uint8_t val) {

    uint8_t tx_buf[1] = {val};
 
    _write_burst(reg, tx_buf, 1);

    return 1;
}


void Lis2Mdl::_write_burst(uint8_t reg, const uint8_t* tx_buf, uint8_t len) {

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