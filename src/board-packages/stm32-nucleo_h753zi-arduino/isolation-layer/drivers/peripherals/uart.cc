#include "core/isolation-layer/peripherals/uart.h"

#include <HardwareSerial.h>
// Uses Serial3 because the VCOM port is set to that

namespace Cesium {

Uart::Uart(uint32_t baud_rate, int8_t uart_instance, const char* port_name) 
    : _baud_rate(baud_rate), _uart_instance(uart_instance), _uart_name{port_name} {}

bool Uart::initialize()
{
    Serial3.begin(_baud_rate, SERIAL_8N1); // May want to change? not sure
    return true;
}

bool Uart::available()
{
    return Serial3.available();
}

uint8_t Uart::read()
{
    
    return static_cast<uint8_t>(Serial3.read());
}

// uint32_t Uart::transmit(String data)
// {
//     return Serial3.print(data);
// }

uint32_t Uart::transmit(char data)
{
    return Serial3.print(data);
}

/**
 * C string
 */
uint32_t Uart::transmit(const char* data)
{
    return Serial3.print(data);
}

} // namespace Cesium