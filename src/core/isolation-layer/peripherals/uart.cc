#include "core/isolation-layer/peripherals/uart.h"

namespace Cesium {


uint32_t Uart::transmitln(char data) {
    return transmit(data) + transmit((char)'\n');
}

uint32_t Uart::transmitln(const char* data, uint32_t len) {
    return transmit(data, len) + transmit((char)'\n');
}

uint32_t Uart::transmit_bytes(uint8_t *bytes, uint32_t len, bool end_line) {
    char hex_byte[5] = {'0', 'x', 0, 0, ' '};

    for (uint32_t i = 0; i < len; i++) {
        uint8_t lower = (bytes[i] & 0x0F) + '0';
        uint8_t upper = ((bytes[i] >> 4) & 0xF) + '0';

        // Letter for hex
        if (lower > 0x39) lower += 7;
        if (upper > 0x39) upper += 7;

        hex_byte[2] = upper;
        hex_byte[3] = lower;

        transmit(hex_byte, 5);
    }
    
    
    if (end_line) {
        transmit('\n');
    }

    return 0;
}

uint32_t Uart::transmit_byte(uint8_t byte, bool end_line)
{
    return transmit_bytes(&byte, 1, end_line);
}

} // namespace Cesium
