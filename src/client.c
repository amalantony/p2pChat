#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAX_BUFLEN 1024


// set the port number and address of server below

#define set_port(s) \
	strcpy(s, "60000")

#define set_server(s) \
	strcpy(s, "192.168.2.4")
	

int main(){
	struct addrinfo hints;
	struct addrinfo *result;
	char port_no[8], server_address[30];
	int status;
	int socket_fd; // socket file descriptor
	set_port(port_no);
	set_server(server_address);
	
	//ensuring hints is empty and calling getaddrinfo()
	memset(&hints, 0, sizeof(struct addrinfo));	
	
	//filling in hints with required values
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	if(status = getaddrinfo(server_address, port_no, &hints, &result )!=0){
		printf("getaddrinfo() error : %s", gai_strerror(status));
		exit(EXIT_FAILURE);
	}
	
	if(socket_fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol) == -1)	{
		printf("Error creating socket to server! \n");
	}
	
	if(connect(socket_fd, result->ai_addr, result->ai_addrlen)==-1){
		printf("Error connecting!\n");
		exit(EXIT_FAILURE);	
	}
}
