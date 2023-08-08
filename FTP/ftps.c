#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<unistd.h>

void main() {
    int server_socket, client_socket, read_size;
    struct sockaddr_in server, client;
    char buffer[1024];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) 
        printf("Socket creation failed");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 8080;
    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) < 0)
        printf("Binding failed");

    listen(server_socket, 3);
    printf("FTP server listening on port");

    while (1) {
    
        int client_address_size = sizeof(struct sockaddr_in);
        client_socket = accept(server_socket, (struct sockaddr*)&client, (socklen_t*)&client_address_size);
        if (client_socket < 0) 
            printf("Accept failed");

        printf("Connected to client: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        FILE* file = fopen("recvfile.txt", "w");
        if (!file)
            printf("File opening failed");

        while ((read_size = recv(client_socket, buffer, sizeof(buffer), 0)) > 0)
            fwrite(buffer, sizeof(char), read_size, file);

        fclose(file);
        printf("File received and saved as 'received_file.txt'\n");

        close(client_socket);
    }
    close(server_socket);
}
