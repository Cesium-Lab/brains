#include "icm20948.h"


namespace Cesium::Sensor {

// Icm20948::Icm20948(SpiPort spi, uint8_t cs_pin) 
//     : _cs_pin{cs_pin}, _spi{spi} {
//     _spi.CS = _cs_pin;
// }

Icm20948::Icm20948(Spi spi, uint8_t cs_pin) 
    : _spi{spi}, _cs_pin{cs_pin} {
        Gpio::init_digital(_cs_pin, GpioType::DIGITAL_OUT);
    }

    
uint8_t Icm20948::_read_single(uint8_t reg) {
    
    Gpio::write_digital(_cs_pin, true);
    _spi.begin_transaction();

    _spi.transfer(reg | 0x80); // read mask
    uint8_t result = _spi.transfer(0x00);

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, false);  
    
    return result;
}


void Icm20948::_read_burst(uint8_t reg, uint8_t* buffer, uint8_t len) {

    Gpio::write_digital(_cs_pin, true);
    _spi.begin_transaction();

    _spi.transfer(reg | 0x80); // read mask
    for (uint8_t i = 0; i < len; i++) {
        buffer[i] = _spi.transfer(0x00);
    }

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, false);
}


uint8_t Icm20948::_write_single(uint8_t reg, uint8_t val) {

    Gpio::write_digital(_cs_pin, true);
    _spi.begin_transaction();

    _spi.transfer(reg & 0x7F); // write mask
    _spi.transfer(val);

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, false); 
}


void Icm20948::_write_burst(uint8_t reg, const uint8_t* buffer, uint8_t len) {

    Gpio::write_digital(_cs_pin, true);
    _spi.begin_transaction();

    _spi.transfer(reg & 0x7F); // write mask
    for (uint8_t i = 0; i < len; i++) {
        _spi.transfer(buffer[i]);
    }

    _spi.end_transaction();
    Gpio::write_digital(_cs_pin, false); 
}

void Icm20948::_select_user_bank(uint8_t bank) {
    bank = bank << 4;
    _write_burst(REG_BANK_SEL, &bank, 1);
}



// class Icm20948 {
//   public:
//     Icm20948(uint8_t cs_pin);

//     // 
//     void select_user_bank(uint8_t bank);
    
//     void read_burst(int8_t reg, uint8_t* buffer, uint8_t len);

//     void write_burst(int8_t reg, const uint8_t* buffer, uint8_t len);

//   protected:
//     SpiPort _spi;
// };


} // namespace Cesium::Sensor