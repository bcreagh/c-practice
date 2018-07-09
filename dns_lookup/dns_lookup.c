/*
This code takes a hostname (e.g. "www.example.com") as input. 
It performs a DNS lookup and prints out and IP addresses associated with the hostname.


This code is heavily based off of code in "Beej's Guide to Network Programming". 
It is a really great guide for network programming, I would highly recommend it.
*/

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //this is where functions such as memset, strcpy, etc. are declared
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>


int main (int argc, char *argv[]) {
	struct addrinfo hints, *results, *p;
	int status;
	char ip_address_string[INET6_ADDRSTRLEN];
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; //This indicates that we don't care whether it's IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;
	
	if((status = getaddrinfo(argv[1], NULL, &hints, &results)) != 0) {
		fprintf(stderr, "There was an problem resolving the hostname: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}

	for(p = results; p != NULL; p = p->ai_next) {
		
		char *ip_version;
		void *ip_address;

		if(p->ai_family == AF_INET) {
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			ip_address = &(ipv4->sin_addr);
			ip_version = "IPv4";
		} else {
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			ip_address = &(ipv6->sin6_addr);
			ip_version = "IPv6";
		}
		
		inet_ntop(p->ai_family, ip_address, ip_address_string, sizeof ip_address_string);
		printf("%s: %s\n", ip_version, ip_address_string);
		
	}

	freeaddrinfo(results);

	return 0;

}

