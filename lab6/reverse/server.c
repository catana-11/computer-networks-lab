#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {

    int server_fd;

    struct sockaddr_in server_addr, client_addr;

    socklen_t addr_len = sizeof(client_addr);

    char buffer[1024];

    char temp;

 
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);


    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    printf("UDP server waiting for message...\n");
    int n = recvfrom(server_fd, buffer, sizeof(buffer) - 1, 0,(struct sockaddr *)&client_addr, &addr_len);

    if (n >= 0) {
        
        buffer[n] = '\0';
        printf("Received string: %s\n", buffer);

      
        for (int i = 0, j = n - 1; i < j; i++, j--) {
            temp = buffer[i];
            buffer[i] = buffer[j];
            buffer[j] = temp;
        }

        printf("Reversed string: %s\n", buffer);

   
        sendto(server_fd, buffer, n, 0,(struct sockaddr *)&client_addr, addr_len);
    } 
    else {
        perror("Receive failed");
    }

    close(server_fd);
    return 0;
}
