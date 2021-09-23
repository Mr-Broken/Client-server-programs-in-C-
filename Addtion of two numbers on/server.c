#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>

#define MAX_MSG 100
#define server_addr "127.0.0.1"
#define server_port 3333


int main()
{
	int sd, newsd, clilen, n, num1, num2, sum;
	
	struct sockaddr_in cliAddr, servAddr;
	
	char line[MAX_MSG], line1[MAX_MSG], line2[MAX_MSG];
	
	//building server address structure
	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(server_addr);
	servAddr.sin_port =htons(server_port);
	
	//creating stream socket
	sd = socket(AF_INET, SOCK_STREAM, 0);
	printf("\nSocket created successfully\n");
	
	//binding local port number
	bind(sd, (struct sockaddr *)&servAddr, sizeof(servAddr));
	printf("Bound local port successfully\n");
	
	//specify number of concurrent
	//client to listen for
	listen(sd,5);
	
	while(1){
	printf("Waiting for client connection on port %u\n", server_port);
	
	clilen = sizeof(cliAddr);
	newsd = accept(sd, (struct sockaddr *)&cliAddr, &clilen);
	
	printf("Recieved connection from host [IP %s, TCP port %d]\n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
	
	//waiting for data from the client
	do {
		memset(line, 0x0, MAX_MSG);
		
		n= recv(newsd, line, MAX_MSG, 0);
		num1=atoi(line);
		printf("\n1st number recieved form client: %d", num1);
		
		n=recv(newsd, line, MAX_MSG, 0);
		num2=atoi(line);
		printf("\n2nd number recieved form client: %d", num2);
		
		sum=num1+num2;
		
		sprintf(line1, "%d", sum);
		
		printf("\nThe sum of recived number sended to the host [IP %s, TCP port %d]: %s\n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), line1);
		
		send(newsd, line1,strlen(line1)+1, 0);
	}while(abs(strcmp(line, "quit")));
	
	printf("Closing connection with host [IP 5s, TCP port %d]\n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
	
	close(newsd);

	}
}
		

