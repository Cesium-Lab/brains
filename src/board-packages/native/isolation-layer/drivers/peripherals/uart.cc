#include "core/isolation-layer/peripherals/uart.h"

#include <cstdio>
// using namespace std;
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

namespace Cesium {

Uart::Uart(uint32_t baud_rate, int8_t uart_instance) 
    : _baud_rate(baud_rate), _uart_instance(uart_instance) {}

bool Uart::initialize()
{
    const char* portName = "/dev/tty.usbserial-0001"; // or "/dev/tty.SLAB_USBtoUART" on macOS
    _uart_instance = open(portName, O_RDWR | O_NOCTTY | O_NONBLOCK);

    if (_uart_instance == -1) {
        perror("Error opening serial port");
        return false;
    }

    termios tty{};
    if (tcgetattr(_uart_instance, &tty) != 0) {
        perror("Error getting termios attributes");
        close(_uart_instance);
        return false;
    }

    // Configure baud rate
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    // 8N1 mode
    tty.c_cflag &= ~PARENB; // No parity
    tty.c_cflag &= ~CSTOPB; // One stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;     // 8 bits per byte

    // tty.c_cflag &= ~CRTSCTS; // No flow control
    tty.c_cflag |= CREAD | CLOCAL; // Enable read & ignore ctrl lines

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw mode
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);         // No software flow control
    tty.c_oflag &= ~OPOST;                          // Raw output

    tcsetattr(_uart_instance, TCSANOW, &tty);

    return true;
}

// bool Uart::available()
// {
//     return Serial.available();
// }

// uint8_t Uart::read()
// {
    
//     return static_cast<uint8_t>(Serial.read());
// }

// uint32_t Uart::transmit(String data)
// {
//     return Serial.print(data);
// }

uint32_t Uart::transmit(char data)
{
    return write(_uart_instance, &data, 1);
}

uint32_t Uart::transmit(const char* data)
{
    return write(_uart_instance, data, strlen(data));
}


} // namespace Cesium
