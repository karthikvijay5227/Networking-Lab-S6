#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netdb.h>

int main()
{
	char buffer[100];	
	int k;
	struct sockaddr_in server,client;
	int sock_desc = socket(AF_INET,SOCK_DGRAM,0);
	if(sock_desc == -1)
		printf("Error in socket()\n");
		
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port = 2060;

	socklen_t client_len = sizeof(client);

	for(;;)
	{
		printf("\nEnter the number to check prime:");
		fgets(buffer,100,stdin);
		if(strncmp("exit",buffer,4)==0 || strncmp("Exit",buffer,4)==0)
		{
			k = sendto(sock_desc,buffer,sizeof(buffer),0,(struct sockaddr*) &server,sizeof(server));
			if(k == -1)
				printf("Error in exit request");
			printf("Exit Request Sent!\nExiting!!!\n");
			break;
		}
		else
		{
			k = sendto(sock_desc,buffer,sizeof(buffer),0,(struct sockaddr*) &server,sizeof(server));
			if(k == -1)
				printf("\nError in sendto()");
			k = recvfrom(sock_desc,buffer,100,0,(struct sockaddr *) &client,&client_len);
			if(k == -1)
				printf("\nError in recvfrom()");
			printf("%s\n",buffer);
		}
	}
	return 0;
}
