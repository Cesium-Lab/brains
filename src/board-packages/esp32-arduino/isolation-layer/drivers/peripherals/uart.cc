#include "core/isolation-layer/peripherals/uart.h"
#include <HardwareSerial.h>
// #ifdef ESP32_ARDUINO
// #include "board-packages/esp32-arduino/drivers/peripherals/uart.h"
// #endif

namespace Cesium {

Uart::Uart(uint32_t baud_rate, int8_t uart_instance) 
    : _baud_rate(baud_rate), _uart_instance(uart_instance) {}

bool Uart::initialize()
{
    Serial.begin(_baud_rate, SERIAL_8N1); // May want to change? not sure
    return true;
}

bool Uart::available()
{
    return Serial.available();
}

uint8_t Uart::read()
{
    
    return static_cast<uint8_t>(Serial.read());
}

// uint32_t Uart::transmit(String data)
// {
//     return Serial.print(data);
// }

uint32_t Uart::transmit(char data)
{
    return Serial.print(data);
}

/**
 * C string
 */
uint32_t Uart::transmit(const char* data)
{
    return Serial.print(data);
}

} // namespace Cesium