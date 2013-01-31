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
	strcpy(s, "127.0.0.1")
	

int main(){
	struct addrinfo hints;
	struct addrinfo *result;
	char port_no[8], server_address[30], buffer[MAX_BUFLEN];
	int status;
	int socket_fd; // socket file descriptor
	set_port(port_no);
	set_server(server_address);
	
	//ensuring hints is empty and calling getaddrinfo()
	memset(&hints, 0, sizeof(struct addrinfo));	
	
	//filling in hints with required values
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	if((status = getaddrinfo(server_address, port_no, &hints, &result ))!=0){
		printf("getaddrinfo() error : %s", gai_strerror(status));
		exit(EXIT_FAILURE);
	}
	
	if((socket_fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == -1)	{
		printf("Error creating socket to server! \n");
	}
	
	printf("%d ", result->ai_addrlen);
	if(connect(socket_fd, result->ai_addr, result->ai_addrlen)==-1){
		perror("Error connecting!\n");
		exit(EXIT_FAILURE);	
	}
	// sending sample data to buffer
	strcpy(buffer,"amalantony@gmail.com");
	write(socket_fd, buffer, MAX_BUFLEN);
}
