
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {

    int server_fd, client_fd;

    struct sockaddr_in server_addr, client_addr;

    socklen_t addr_len = sizeof(client_addr);

    char buffer[1024];

    // create tcp socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // configure server address

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;

    /*
    Allows the server to accept connections addressed to any of the local machine's IPv4 network interfaces, subject to firewall and network configuration.
    For example, the server can listen on the loopback interface and a local network interface rather than being restricted to just one specified address.
    */

    server_addr.sin_port = htons(8080);

    // bind socket to ip and port
    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    // listen for client connections
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        return 1;
    }

    /*
    The value 5 is not a limit of five total clients. 
    It specifies the requested queue size for connections waiting to be accepted; the operating system may adjust it.
    */

    printf("Server waiting for client...\n");

    // accept client connection
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                       &addr_len);

    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        return 1;
    }

    printf("Client connected!\n");

    // receive message from client

    memset(buffer, 0, sizeof(buffer));
    int n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (n > 0) {
        buffer[n] = '\0';
        printf("Client: %s\n", buffer);
        // send reply to client
        printf("Enter reply: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        send(client_fd, buffer, strlen(buffer), 0);
    }

    // close connections
    close(client_fd);
    close(server_fd);

    return 0;
}
