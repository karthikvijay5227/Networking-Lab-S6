#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

void main()
{
	int k,sock_desc;
	char buf[100];
	struct sockaddr_in client;
	
	sock_desc = socket(AF_INET,SOCK_STREAM,0);
	if(sock_desc == -1)
		printf("Error in socket creation");
		
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = 8080;
	
	k = connect(sock_desc,(struct sockaddr*)&client,sizeof(client));
	if(k == -1)
		printf("Error in connection");
		
	printf("Connection successful\n");
	
	FILE* file = fopen("sendf.txt","r");
	if(!file)
		printf("File opening error");
		
	while(!feof(file))
	{
		size_t read_size = fread(buf,sizeof(char),sizeof(buf),file);
		if(send(sock_desc,buf,read_size,0) < 0)
			printf("Send failed");
	}
	fclose(file);
    printf("File sent successfully\n");
	close(sock_desc);
}
