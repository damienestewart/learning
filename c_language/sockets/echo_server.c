#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>

int main(int argc, char **argv) {

	int MAX_LEN = 1024;
	char END_CONNECTION[] = "quit\r\n";

	char buffer[MAX_LEN];
	int socket_fd, client_socket_fd;
	struct sockaddr_in *address = (struct sockaddr_in *) calloc(1, sizeof(struct sockaddr_in));
	socklen_t address_len = sizeof(struct sockaddr_in);
	
	socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	address->sin_family = AF_INET;
	address->sin_port = htons(3000);
	address->sin_addr.s_addr = INADDR_ANY;	

	memset(buffer, 0, 1024);

	if (bind(socket_fd, (struct sockaddr*) address, address_len) < 0) {
		// check errno.
		exit(1);	
	}

	if (listen(socket_fd, SOMAXCONN) < 0) {
		// check errno.
		exit(1);
	}

	client_socket_fd = accept(socket_fd, NULL, NULL);

	while (1) {

		if (read(client_socket_fd, buffer, sizeof(buffer)) <= 0) {
			// handle error
			exit(1);
		}

		if (!strcmp(buffer, END_CONNECTION)) {
			close(client_socket_fd);
			exit(1);
		}
	
		if (write(client_socket_fd, buffer, sizeof(buffer)) <= 0) {
			// handle error
			exit(1);
		}

		memset(buffer, 0, MAX_LEN);
	}

	return 0;
}
