/*
This code is an extremely simple "server". It listens on port 3301. 
When a client connects, its sends a simple "Hello World" message to the client.


This code is heavily based off of code in "Beej's Guide to Network Programming". 
It is a really great guide for network programming, I would highly recommend it.
*/

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>



// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa);

int main(int argc, char *argv[]) {

	struct addrinfo *server_info, *p, hints;
	int socket_descriptor;
	int client_socket_descriptor;
	int success_status;
	int yes = 1;
	socklen_t client_address_length;
	struct sockaddr_storage client_address;
	char client_address_string[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;	

	if((success_status = getaddrinfo(NULL, "3301", &hints, &server_info)) != 0) {
		fprintf(stderr, "Error when calling getaddrinfo(): %s\n", gai_strerror(success_status));
		return 1;
	}
	
	for(p = server_info; p != NULL; p = p->ai_next){
		if((socket_descriptor = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol)) == -1) {
			perror("Error when calling socket(): ");
			continue;
		}

		if (setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &yes,
			sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}
		
		if(bind(socket_descriptor, server_info->ai_addr, server_info->ai_addrlen) == -1){
			close(socket_descriptor);
			perror("Error when calling bind(): ");
			continue;
		}
		
		break;
	}
	
	freeaddrinfo(server_info);

	if(p == NULL) {
		fprintf(stderr, "Could not successfully bind to a port to listen on %s\n", "");
	}
	
	

	if(listen(socket_descriptor, 10) == -1){
		perror("Error when calling listen(): ");
		return 1;
	}
	
	while(1) {
		client_address_length = sizeof client_address;
		if ((client_socket_descriptor = accept(socket_descriptor, (struct sockaddr *)&client_address, &client_address_length)) == -1) {
			perror("Error when calling accept(): ");
			continue;
		}
		
		inet_ntop(client_address.ss_family, get_in_addr((struct sockaddr *)&client_address), client_address_string, sizeof client_address_string);
		printf("Got a connection from: %s\n", client_address_string);


		char my_resp[] = "Hello world!";
		int my_len = strlen(my_resp);
		
		if(send(client_socket_descriptor, my_resp, my_len, 0) == -1) {
			perror("Error when calling send: ");
		}
		close(client_socket_descriptor); 
	}
	
	
	return 0;
}

void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
