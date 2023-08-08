#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>

int main()
{
	int num;
	struct sockaddr_in server, client;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1)
		printf("Error in socket creation");
		
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = 2060;
	
	if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
		printf("Error in binding\n");
		
	socklen_t server_len = sizeof(server);
	printf("Server is running on %s\n",inet_ntoa(server.sin_addr));
	while(1)
	{
		recvfrom(sockfd, &num,sizeof(num), 0, (struct sockaddr *)&server, &server_len);
		time_t current_time = time(NULL);
		printf("Client asked for time:%s",ctime(&current_time));
		sendto(sockfd, &current_time, sizeof(current_time), 0, (struct sockaddr *)&server, sizeof(server));
		exit(0);
	}
return 0;
}
