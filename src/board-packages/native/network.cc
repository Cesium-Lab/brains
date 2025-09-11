#include "core/isolation-layer/network.h"

namespace Cesium::Network {

UdpSender::UdpSender(in_addr_t ip, uint16_t port)

{
    /* 1. Create socket */
    _socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
                    // use IPv4  use UDP
                    
    /* 2. Construct server address */
    _receiver_addr.sin_family = AF_INET; // use IPv4
    _receiver_addr.sin_addr.s_addr = ip;

    // Set sending port
    _receiver_addr.sin_port = htons(port); // Big endian

    _serversize = sizeof(sockaddr_in); // Temp buffer for recvfrom API
    
}

UdpSender::UdpSender(sockaddr_in receiver_addr)
{
    _receiver_addr = receiver_addr;
}
int UdpSender::send_message(const char *message)
{                
    /* 3. Send data to server */
    int did_send = sendto(_socket_fd, message, strlen(message), 
                    //. socket  send data   how much to send
                        0, (struct sockaddr*) &_receiver_addr, 
                    // flags   where to send
                        sizeof(_receiver_addr));
    
    return did_send;
}

int UdpSender::listen(char* buffer, int buffer_size)
{                
    int bytes_recvd = recvfrom(_socket_fd, buffer, buffer_size, 
                                // socket  store data  how much
                                0, (struct sockaddr*) &_receiver_addr, 
                                &_serversize);

    // Clamping to 0 just in case
    if (bytes_recvd <= 0) return 0;      
    
    return bytes_recvd;
}

} // namespace Cesium::Network