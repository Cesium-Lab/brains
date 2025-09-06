#include <netinet/in.h> // Everything
// #include <sys/socket.h> // Not sure what this includes
// #include <arpa/inet.h> // Not sure what this includes
#include <string.h> // strlen
#include <unistd.h> // Standard out
#include <fcntl.h> // Non-blocking
#include <chrono>

#include "core/isolation-layer/time.h"

class UdpConnection
{
public:
    // Currently only supports localhost
    UdpConnection(in_addr_t ip = INADDR_ANY, uint16_t port = 8080)
    {
        /* 1. Create socket */
        _socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
                        // use IPv4  use UDP
                        
        /* 2. Construct server address */
        _serveraddr.sin_family = AF_INET; // use IPv4
        _serveraddr.sin_addr.s_addr = ip;

        // Set sending port
        _serveraddr.sin_port = htons(port); // Big endian

        _serversize = sizeof(sockaddr_in); // Temp buffer for recvfrom API
        
    }

    int send_message(const char* message)
    {

        /* 3. Send data to server */
        int did_send = sendto(_socket_fd, message, strlen(message), 
                        //. socket  send data   how much to send
                            0, (struct sockaddr*) &_serveraddr, 
                        // flags   where to send
                            sizeof(_serveraddr));
        
        return did_send;
    }

    /*
        Must call within a while loop to continuously get messages

        Returns number of new bytes
    */
    int listen(char* buffer, int buffer_size = 1024) {                
        int bytes_recvd = recvfrom(_socket_fd, buffer, buffer_size, 
                                    // socket  store data  how much
                                    0, (struct sockaddr*) &_serveraddr, 
                                    &_serversize);

        // Clamping to 0 just in case
        if (bytes_recvd <= 0) return 0;      
        
        return bytes_recvd;
    }

private:
    // File descriptor
    int _socket_fd;

    // Socket address struct (with ip, port)
    sockaddr_in _serveraddr;

    // Size of server address?
    socklen_t _serversize;
};

int main()
{
    UdpConnection connection;

    // connection.send_message("1. Hello world from client!\n");
    // connection.send_message("2. Hello world from client!\n");
    // connection.send_message("3. Hello world from client!\n");
    // connection.send_message("4. Hello world from client!\n");
    // connection.send_message("5. Hello world from client!\n");
    // connection.send_message("6. Hello world from client!\n");
    // connection.send_message("7. Hello world from client!\n");


    int BUF_SIZE = 1024;
    char server_buf[BUF_SIZE];  

    char l[] = "a";
    
    while(1)
    {

        connection.send_message("Hello world from client! ");
        connection.send_message(l);
        connection.send_message("\n");

        int bytes_recvd = connection.listen(server_buf, BUF_SIZE);

        if (bytes_recvd > 0)
        {
            write(1, server_buf, bytes_recvd); 
        }

        l[0]++;

        Cesium::Time::delay(1000);
    }
    
    return 0;

}


// int main() {
//     /* 1. Create socket */
//     int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//                      // use IPv4  use UDP

//     // Setup fd set for nonblock
//     // int flags = fcntl(sockfd, F_GETFL);
//     // flags |= O_NONBLOCK;
//     // fcntl(sockfd, F_SETFL, flags);

//     /* 2. Construct server address */
//     struct sockaddr_in serveraddr;
//     serveraddr.sin_family = AF_INET; // use IPv4
//     serveraddr.sin_addr.s_addr = INADDR_ANY;
//     // Set sending port
//     int SEND_PORT = 8080;
//     serveraddr.sin_port = htons(SEND_PORT); // Big endian

//     /* 3. Send data to server */
//     char client_buf[] = "Hello world from client!\n";
//     int did_send = sendto(sockfd, client_buf, strlen(client_buf), 
//                        //. socket  send data   how much to send
//                           0, (struct sockaddr*) &serveraddr, 
//                        // flags   where to send
//                           sizeof(serveraddr));
//     if (did_send < 0) return errno;

//     /* 4. Create buffer to store incoming data */
//     int BUF_SIZE = 1024;
//     char server_buf[BUF_SIZE];
//     socklen_t serversize = sizeof(sockaddr_in); // Temp buffer for recvfrom API



//     /* 5. Listen for response from server */
//     while (1) {
//         /* Do some processing here */
            
//         int bytes_recvd = recvfrom(sockfd, server_buf, BUF_SIZE, 
//                                     // socket  store data  how much
//                                     0, (struct sockaddr*) &serveraddr, 
//                                     &serversize);
//         // No data yet, we can continue processing at the top of this loop
//         if (bytes_recvd <= 0) continue;              
                                
//         /* Data available; we can now process the data */    

//         // Print out data
//         write(1, server_buf, bytes_recvd);              
//     }

//     // OLD
//     int bytes_recvd = recvfrom(sockfd, server_buf, BUF_SIZE, 
//                             // socket  store data  how much
//                                0, (struct sockaddr*) &serveraddr, 
//                                &serversize);
//     // Execution will stop here until `BUF_SIZE` is read or termination/error
//     // Error if bytes_recvd < 0 :(
//     if (bytes_recvd < 0) return errno;
    
//     // Print out data
//     write(1, server_buf, bytes_recvd);   
//     char msg[] = "Transmit!\n";
//     write(STDOUT_FILENO, msg, sizeof(msg));   

//     /* 6. You're done! Terminate the connection */     
//     close(sockfd);
//     return 0;
// }
