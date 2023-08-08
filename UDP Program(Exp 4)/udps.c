#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>

int main()
{
	char buffer[100];
	int k;
	struct sockaddr_in server,client;
	int sock_desc = socket(AF_INET,SOCK_DGRAM,0);
	if(sock_desc==-1)
		printf("Error in socket creation");
		
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port = 2060;
	
	if(bind(sock_desc,(struct sockaddr*)&server,sizeof(server))<0)
		printf("Error in binding\n");

	socklen_t len = sizeof(server);
	for(;;)
	{
		k = recvfrom(sock_desc,buffer,100,0,(struct sockaddr *) &server,&len);
		if(k<0)
			printf("Error in receiving");
		if(strncmp("exit",buffer,4)==0||strncmp("Exit",buffer,4)==0)
		{
			printf("Received exit request from client!\nExiting!!!");
			break;
		}
		else
		{
			printf("\nMessage from Client:%s",buffer);
			printf("Enter data to send to client:");
			fgets(buffer,100,stdin);
			printf("\n");
			k = sendto(sock_desc,buffer,sizeof(buffer),0,(struct sockaddr*) &server,sizeof(server));
			if(k<0)
				printf("Error in sending");
		}
	}
	return 0;
}
	
