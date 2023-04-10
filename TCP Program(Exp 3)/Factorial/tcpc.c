#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
int main()

{
	char buf[100];
	int k;
	socklen_t len;
	int sock_desc;
	struct sockaddr_in server,client;
	sock_desc=socket(AF_INET, SOCK_STREAM,0);

	if(sock_desc==-1)
		printf("Error in Socket creation\n");

	client.sin_family=AF_INET;
	client.sin_addr.s_addr=INADDR_ANY;

	client.sin_port=3003;
	k=connect(sock_desc, (struct sockaddr*) &client, sizeof(client));

	if(k==-1)
		printf("Error in connecting to server\n");
	for(;;)
	{
		printf("\nEnter data to be send:");
		fgets(buf,100,stdin);
		if(atoi(buf)==1111)
		{
			k=send(sock_desc,buf,100,0);
			printf("Exit Request Sent!\nExiting!!!");	
			exit(0);
		}
		k=send(sock_desc,buf,100,0);
		if(k==-1)
			printf("Error in sending\n");
		k=recv(sock_desc,buf,100,0);
		if(k==-1)
			printf("Error in receiving\n");
		printf("The factorial of number passed to server is:%s\n",buf);
	}
	close(sock_desc);
	return 0;
}
	
