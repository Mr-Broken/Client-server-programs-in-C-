#Written by Cyber_boy

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>

#define MAX_MSG 100
#define server_addr "127.0.0.1"
#define client_addr "127.0.0.1"
#define server_port 3333
#define client_port 4444

int main()
{
	int sd, rc, i, n;
	struct sockaddr_in clientAddr, servAddr;
	char line[MAX_MSG];
	
	//building server address structure
	
	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(server_addr);
	servAddr.sin_port = htons(server_port);
	
	//building client address structure
	bzero((char *)&clientAddr, sizeof(clientAddr));
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_addr.s_addr = inet_addr(client_addr);
	clientAddr.sin_port = htons(client_port);
	
	//Creating stream socket
	sd = socket(AF_INET, SOCK_STREAM, 0);
	printf("successfully created stream socket\n");
	
	//binding port number
	bind(sd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
	printf("binded local port successfully\n");
	
	//connecting to server
	connect(sd, (struct sockaddr *)&servAddr, sizeof(servAddr));
	printf("Connected to server successfully\n");
	
	//seding data to server
	do {
	printf("Please enter your 1st number: ");
	scanf("%s", line);
	
	send(sd, line, strlen(line) +1, 0);
	printf("data sent(%s)\n", line);
	
	printf("Please enter your 2nd number: ");
	scanf("%s", line);
	send(sd, line, strlen(line) +1, 0);
	printf("data sent(%s)\n", line);
	
	//receving data from server
	
	n = recv(sd, line, MAX_MSG, 0);
	printf("\nRecieved sum of the above number from server is %s\n", line);
	}while(strcmp(line, "quit"));
	
	printf("\nClosing connection with the server\n");
	
	close(sd);
}
