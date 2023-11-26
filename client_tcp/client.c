#include "../include/client.h"
#include <sys/socket.h>
#include <stdio.h>

void client_start()
{
	int client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket_fd < 0) {
		perror("Can't start client socket");
	} else {
		LOG_INFO("Client socket creater: %d", client_socket_fd);
	}
}

/*
 * Client main
 */

int main()
{
	client_start();
	return 0;
}
