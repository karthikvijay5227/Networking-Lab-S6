#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<unistd.h>

void main() {
    int socket_desc;
    struct sockaddr_in server;
    char buffer[1024];

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 8080;

    if (connect(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) 
        printf("Connection failed");
    printf("Connected to FTP server\n");

    FILE* file = fopen("fsend.txt", "r");
    if (!file) 
        printf("File opening failed");

    while (!feof(file)) {
        size_t read_size = fread(buffer, sizeof(char), sizeof(buffer), file);
        if (send(socket_desc, buffer, read_size, 0) < 0)
            printf("Send failed");
    }

    fclose(file);
    printf("File sent successfully\n");

    close(socket_desc);
}
