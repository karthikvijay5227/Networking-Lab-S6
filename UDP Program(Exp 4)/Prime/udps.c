#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netdb.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(int n) {

    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}
int main(int argc,char *argv[])
{
	struct sockaddr_in server,client;
	if(argc!=2)
		printf("Input format not correct");
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	int f=1,i=0;
	if(sockfd==-1)
		printf("Error in socket()");
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));
	if(bind(sockfd,(struct sockaddr*) &server,sizeof(server))<0)
		printf("Error in bind()\n");
	char buffer[100];
	socklen_t server_len = sizeof(server);
	for(;;)
	{
		int k = recvfrom(sockfd,buffer,100,0,(struct sockaddr *) &server,&server_len);
		if(k<0)
			printf("Error in recvfrom()");
		if(strncmp("exit",buffer,4)==0 || strncmp("Exit",buffer,4)==0)
		{
			printf("Received exit request from client!\nExiting!!!\n");
			break;
		}
		printf("Message from Client:%s\n",buffer);
		int n = atoi(buffer);
		bool isPrime = is_prime(n);
		strcpy(buffer,isPrime ? "Number is Prime" : "Number is Not Prime");
		k = sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*) &server,sizeof(server));
		if(k<0)
			printf("Error in sendto()");
	}
	return 0;
}
