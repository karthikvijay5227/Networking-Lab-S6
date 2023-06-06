#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include<time.h>

int main(int argc, char *argv[])
{
	int num;
	struct sockaddr_in server, client;
	if (argc != 2)
		printf("Input format not correct");
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1)
		printf("Error in socket()");
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));
	if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
		printf("Error in bind()\n");
	socklen_t server_len = sizeof(server);
	printf("Server is running on 127.0.0.1\n");
	while(1)
	{
		recvfrom(sockfd, &num,sizeof(num), 0, (struct sockaddr *)&server, &server_len);
		time_t current_time = time(NULL);
		printf("Client asked for time:%s\n",ctime(&current_time));
		sendto(sockfd, &current_time, sizeof(current_time), 0, (struct sockaddr *)&server, sizeof(server));
		exit(0);
	}
return 0;
}