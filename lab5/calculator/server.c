
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

    float a, b, result;

    char op;

    // create tcp socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // config server addrs
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
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

    // receive math input
    int n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (n > 0) {
        buffer[n] = '\0';

        sscanf(buffer, "%f %c %f", &a, &op, &b);

        switch (op) {
            case '+':
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
                if (b == 0) {
                    strcpy(buffer, "Error: Division by zero");
                    send(client_fd, buffer, strlen(buffer), 0);
                    close(client_fd);
                    close(server_fd);
                    return 0;
                }
                result = a / b;
                break;
            default:
                strcpy(buffer, "Invalid operator");
                send(client_fd, buffer, strlen(buffer), 0);
                close(client_fd);
                close(server_fd);
                return 0;
        }

        printf("Received expression: %.2f %c %.2f\n", a, op, b);

        // send result
        snprintf(buffer, sizeof(buffer), "Result = %.2f", result);
        send(client_fd, buffer, strlen(buffer), 0);
    }

    // close
    close(client_fd);
    close(server_fd);

    return 0;
}
