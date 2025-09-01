#include "core/isolation-layer/peripherals/i2c.h"
#include <Wire.h>

namespace Cesium {

TwoWire _wire(0);

I2C::I2C(i2cPort port) : _port{port}
{
    _wire.setPins(_port.SDA, _port.SCL);
}

bool I2C::initialize()
{
    return _wire.begin();
}

void I2C::set_frequency(uint32_t frequency) { _port.frequency = frequency; }

bool I2C::write(uint8_t addr, uint8_t* buff, uint8_t len, bool stop)
{
    Wire.beginTransmission(addr); 

    // Fills the buffer with what I want to write 
    Wire.write(buff, len);

    // Send buffer (with a stop bit)
    return (Wire.endTransmission(stop) == 0);
}

bool I2C::read(uint8_t addr, uint8_t reg, uint8_t* buff, uint8_t len)
{
    // Send address to write reg and return if not written
     if (!write(addr, &reg, 1, false)) return false;

    // Sends address with read, and reads [len] bytes
    uint8_t bytes_read = _wire.requestFrom(addr, len);

    if (bytes_read < len) return false;

    // Read from RX buffer
    for (int i = 0; i < len; i++)
        buff[i] = _wire.read();

    return true;
}


} // namespace Cesium