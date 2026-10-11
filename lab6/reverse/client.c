
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {

    int sock;

    struct sockaddr_in server_addr;

    socklen_t addr_len = sizeof(server_addr);

    char buffer[1024];

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {

        perror("Socket creation failed");
        return 1;
    }


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);


    printf("Enter a string: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';


    sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr *)&server_addr, sizeof(server_addr));


    int n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&server_addr, &addr_len);

    if (n >= 0) {

        buffer[n] = '\0';
        printf("Reversed string from server: %s\n", buffer);
    } 
    else {
        perror("Receive failed");
    }

    close(sock);

    return 0;
}
