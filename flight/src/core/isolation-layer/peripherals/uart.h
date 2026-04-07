#pragma once

#include <stdint.h>
// #include <WString.h> // from Arduino
// #include <etl/array.h>

namespace Cesium {

class Uart { // TODO: will extend from a common base class to swap interfaces
  public:
    Uart(uint32_t baud_rate = 115200, int8_t uart_instance = 0, const char* port_name = nullptr);
    // Uart(uint32_t baud_rate = 115200, uint8_t rx_pin, uint8_t tx_pin,);

    bool initialize();
    
    uint32_t transmit(uint8_t data);
    uint32_t transmit(const char* data); // For just transmitting c strings 
    uint32_t transmit(const uint8_t* data, uint32_t len);

    bool available();
    uint8_t read();
    

  protected:
    uint32_t _baud_rate;
    int8_t _uart_instance;
    const char* _uart_name;
};

} // namespace Cesium
