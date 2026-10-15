
#include <stdio.h>
#include <string.h>
#include <unistd.h>         // gives close()
#include <arpa/inet.h>      // for converting ip addrs and port nos.
#include <sys/socket.h>     // gives socket(), connect(), send(), recv()

int main() {

    int sock; 
    // stores the socket descriptor

    struct sockaddr_in server_addr; 
    // stores server's ipv4 addrs and port nos
    char buffer[1024];


    // create tcp socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // syntax is : socket(domain, type, protocol);
    // af_inet: uses ipv4 addresing
    // sock_stream: Uses a reliable, connection-oriented byte stream, normally TCP
    // 0 : auto selects default protocol for the given domain and type, which  becomes tcp here

    if (sock == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // configure server address

    server_addr.sin_family = AF_INET;       // ipv4 addressing
    server_addr.sin_port = htons(8080);     
    /*
    Converts port 8080 from the computer's host byte order to network byte order (big-endian).
    Return value: The converted 16-bit unsigned integer.
    Port numbers identify services or applications on a device. The server must use the same port. 
    */
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    /*
    Converts the IPv4 address string "127.0.0.1" into binary form and stores it in server_addr.sin_addr.
    */
    // connect to server
    // syntax: connect(socket_descriptor, server_address, address_length);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    // input msg from user
    printf("Enter message: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    // send to server
    //syntax: send(socket_descriptor, data, length, flags);

    send(sock, buffer, strlen(buffer), 0);

    // receive reply from server
    memset(buffer, 0, sizeof(buffer));
    int n = recv(sock, buffer, sizeof(buffer) - 1, 0);

    if (n > 0) {
        buffer[n] = '\0';
        printf("Server: %s\n", buffer);
    }

    // close client socket
    close(sock);

    return 0;
}
