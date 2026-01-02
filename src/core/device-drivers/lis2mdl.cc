#include "core/device-drivers/lis2mdl.h"
#include "core/utilities/bits.h"

#include <cstring> // memset

namespace Cesium::Sensor {

Lis2Mdl::Lis2Mdl(Spi spi, uint8_t cs_pin) 
    : _spi{spi}, _cs_pin{cs_pin} {
    Gpio::init_digital(_cs_pin, GpioType::DIGITAL_OUT);
}

void Lis2Mdl::initialize() {


    // Enables measurement mode
    _write_single(CFG_REG_C, 0b100); // standby
    // _write_single(REG_BW_RATE, 0x0D);   // 800 Hz
    // _write_single(REG_DATA_FORMAT, 0x00); // right-justified, full-res
    // _write_single(REG_POWER_CTL, 0x04); // measurement
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

uint8_t Lis2Mdl::chip_id() {
    return _read_single(REG_WHO_AM_I);
}

lis2mdl_data_t Lis2Mdl::read(uint8_t range)
{

    lis2mdl_data_t result;
    uint8_t buffer[8]{};

    _read_burst(REG_OUTX_L_REG, buffer, 6);

    // Using this 
    result.mag_x = bytes_to_float(buffer[1], buffer[0]) * MAG_LSB_TO_MGAUSS;
    result.mag_y = bytes_to_float(buffer[3], buffer[2]) * MAG_LSB_TO_MGAUSS;
    result.mag_z = bytes_to_float(buffer[5], buffer[4]) * MAG_LSB_TO_MGAUSS;
    result.temp = bytes_to_float(buffer[7], buffer[6]) / TEMP_DEG_C_TO_LSB;

    return result;
}


//////////////////////////////////////////////////
//              Read
//////////////////////////////////////////////////

uint8_t Lis2Mdl::_read_single(uint8_t reg) {

    uint8_t tx[2] = {(uint8_t)(reg | 0x80), 0x00};
    uint8_t rx[2] = {};

    Gpio::write_digital(_cs_pin, false);
    _spi.begin_transaction();

    _spi.transfer(tx, rx, 2); // read mask

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, true);

    return rx[1];
}


void Lis2Mdl::_read_burst(uint8_t reg, uint8_t* rx_buf, uint8_t len) {

    uint8_t tx[len + 1] = {};
    tx[0] = reg | 0x80;
    memset(tx + 1, 0x00, len);
    
    uint8_t rx[len + 1] = {};

    Gpio::write_digital(_cs_pin, false);
    _spi.begin_transaction();

    _spi.transfer(tx, rx, len+1); // read mask

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, true);

    memcpy(rx_buf, rx + 1, len);

}

//////////////////////////////////////////////////
//              Write
//////////////////////////////////////////////////


uint8_t Lis2Mdl::_write_single(uint8_t reg, uint8_t val) {

    uint8_t tx[1] = {val};
 
    _write_burst(reg, tx, 1);

    return 1;
}


void Lis2Mdl::_write_burst(uint8_t reg, const uint8_t* tx_buf, uint8_t len) {

    uint8_t tx[len + 1] = {};
    tx[0] = reg & 0x7F;
    memcpy(tx + 1, tx_buf, len);
    
    uint8_t rx[len + 1] = {};

    Gpio::write_digital(_cs_pin, false);
    _spi.begin_transaction();

    _spi.transfer(tx, rx, len+1); // read mask

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, true);
}


} // namespace Cesium::Sensor