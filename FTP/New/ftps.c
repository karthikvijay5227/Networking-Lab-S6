#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void main()
{
	int k;
	char buf[1024];
	struct sockaddr_in server,client;
	socklen_t len;
	int sock_desc,temp_sock_desc;
	sock_desc = socket(AF_INET,SOCK_STREAM,0);
	if(sock_desc == -1)
		printf("Socket creation error\n");
		
	printf("Connection successfully established\n");
		
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = 8080;
	
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = 8080;
	
	k = bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
	if(k == -1)
		printf("Binding error\n");
	
	k = listen(sock_desc,5);
	if(k == -1)
		printf("Error in listening\n");
		
	while(1)
	{
		len = sizeof(client);
		temp_sock_desc = accept(sock_desc,(struct sockaddr*)&client,&len);
		
		if(temp_sock_desc == -1)
			printf("Accept failed\n");
			
		FILE* file = fopen("recvf.txt","w");
		if(!file)
			printf("File opening error");
			
		while((k = recv(temp_sock_desc,buf,sizeof(buf),0))>0)
			fwrite(buf,sizeof(char),k,file);
			
		fclose(file);
		printf("File saved as recvf.txt\n");
	}
	close(temp_sock_desc);
	close(sock_desc);
}
