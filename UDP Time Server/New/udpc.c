#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>

int main()
{
	int num = 1;
	time_t current_time,rtt;
	struct sockaddr_in server, client;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1)
		printf("Error in socket()\n");
		
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = 2060;
	
	socklen_t client_len = sizeof(client);
	sendto(sockfd, &num, sizeof(num), 0, (struct sockaddr *)&server, sizeof(server));
	time_t start_time = time(NULL);
	clock_t start = clock();
	recvfrom(sockfd, &current_time, sizeof(current_time), 0, (struct sockaddr *)&client, &client_len);
	clock_t end = clock();
	rtt = time(NULL) - start_time;
	current_time = current_time+(rtt/2);
	double diff = (end-start)/2;
	printf("Server's Time:%sDelayed by %.3f milliseconds\n",ctime(&current_time),diff);
	return 0;
}
