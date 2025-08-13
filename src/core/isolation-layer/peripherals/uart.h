#pragma once

#include <stdint.h>
// #include <WString.h> // from Arduino
// #include <etl/array.h>
namespace Cesium {

class Uart { // TODO: will extend from a common base class to swap interfaces
  public:
    Uart(uint32_t baud_rate = 115200, int8_t uart_instance = 0);
    // Uart(uint32_t baud_rate = 115200, uint8_t rx_pin, uint8_t tx_pin,);

    bool initialize();
    // uint32_t transmit(String data);
    uint32_t transmit(char data);
    uint32_t transmit(char* data);

    bool available();
    uint8_t read();
    
    // template<std::size_t SIZE>
    // uint32_t transmit(etl::array<uint8_t, SIZE> arr);

  private:
    uint32_t _baud_rate;
    int8_t _uart_instance;
};

// template <std::size_t SIZE>
// inline uint32_t Uart::transmit(etl::array<uint8_t, SIZE> arr)
// {
//     uint32_t bytes = 0;
//     for (const auto& element : arr) {
//         bytes += this->transmit(element);
//     }

//     return bytes;
// }

} // namespace Cesium