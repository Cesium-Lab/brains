#include "core/isolation-layer/peripherals/uart.h"

namespace Cesium {


uint32_t Uart::transmitln(char data) {
    return transmit(data) + transmit((char)'\n');
}

uint32_t Uart::transmitln(const char* data) {
    return transmit(data) + transmit((char)'\n');
}

uint32_t Uart::transmit_bytes(uint8_t *bytes, uint32_t len, bool end_line) {
    char* hex_byte = "0xNN";

    for (uint32_t i = 0; i < len; i++) {
        uint8_t lower = (bytes[i] & 0xF) + '0';
        uint8_t upper = ((bytes[i] >> 4) & 0xF) + '0';
        hex_byte[2] == lower;
        hex_byte[3] == upper;

        transmit(hex_byte);
    }
    
    
    if (end_line) {
        transmit((char)'\n');
    }

    return 0;
}

uint32_t Uart::transmit_byte(uint8_t byte, bool end_line)
{
    transmit_bytes(&byte, 1, end_line);
}

} // namespace Cesium
