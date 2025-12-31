#include "core/device-drivers/lis2mdl.h"
#include "core/utilities/bits.h"

namespace Cesium::Sensor {

Lis2Mdl::Lis2Mdl(Spi spi, uint8_t cs_pin) 
    : _spi{spi}, _cs_pin{cs_pin} {
    Gpio::init_digital(_cs_pin, GpioType::DIGITAL_OUT);
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
    
    Gpio::write_digital(_cs_pin, true);
    _spi.begin_transaction();

    _spi.transfer(reg | 0x80); // read mask
    uint8_t result = _spi.transfer(0x00);

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, false);  
    
    return result;
}


void Lis2Mdl::_read_burst(uint8_t reg, uint8_t* buffer, uint8_t len) {

    Gpio::write_digital(_cs_pin, true);
    _spi.begin_transaction();

    _spi.transfer(reg | 0x80); // read mask
    for (uint8_t i = 0; i < len; i++) {
        buffer[i] = _spi.transfer(0x00);
    }

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, false);
}

//////////////////////////////////////////////////
//              Write
//////////////////////////////////////////////////


uint8_t Lis2Mdl::_write_single(uint8_t reg, uint8_t val) {

    Gpio::write_digital(_cs_pin, true);
    _spi.begin_transaction();

    _spi.transfer(reg & 0x7F); // write mask
    _spi.transfer(val);

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, false); 
}


void Lis2Mdl::_write_burst(uint8_t reg, const uint8_t* buffer, uint8_t len) {

    Gpio::write_digital(_cs_pin, true);
    _spi.begin_transaction();

    _spi.transfer(reg & 0x7F); // write mask
    for (uint8_t i = 0; i < len; i++) {
        _spi.transfer(buffer[i]);
    }

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, false); 
}


} // namespace Cesium::Sensor