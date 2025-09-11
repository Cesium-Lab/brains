#pragma once

#include <netinet/in.h> // Everything
// #include <sys/socket.h> // Not sure what this includes
// #include <arpa/inet.h> // Not sure what this includes
#include <string.h> // strlen
#include <unistd.h> // Standard out
#include <fcntl.h> // Non-blocking

namespace Cesium::Network {

class UdpSender
{
public:
    // Currently only supports localhost
    UdpSender(in_addr_t ip = INADDR_ANY, uint16_t port = 8080);
    UdpSender(sockaddr_in receiver_addr);

    int send_message(const char* message);

    /*
        Must call within a while loop to continuously get messages

        Returns number of new bytes
    */
    int listen(char* buffer, int buffer_size = 1024);

private:
    // File descriptor
    int _socket_fd;

    // Socket address struct (with ip, port)
    sockaddr_in _receiver_addr;

    // Size of server address?
    socklen_t _serversize;
};




} // namespace Cesium::Network
