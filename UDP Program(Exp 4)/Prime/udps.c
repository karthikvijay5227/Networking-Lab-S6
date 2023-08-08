#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
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
int main()
{
	char buffer[100];
	int f=1,i=0;
	struct sockaddr_in server,client;
	int sock_desc = socket(AF_INET,SOCK_DGRAM,0);
	if(sock_desc==-1)
		printf("Error in socket creation");
		
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port = 2060;
	
	if(bind(sock_desc,(struct sockaddr*) &server,sizeof(server))<0)
		printf("Error in binding\n");
		
	socklen_t len = sizeof(server);
	for(;;)
	{
		int k = recvfrom(sock_desc,buffer,100,0,(struct sockaddr *) &server,&len);
		if(k == -1)
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
		k = sendto(sock_desc,buffer,sizeof(buffer),0,(struct sockaddr*) &server,sizeof(server));
		if(k == -1)
			printf("Error in sendto()");
	}
	return 0;
}
