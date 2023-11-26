#include "../include/client.h"
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

void client_start()
{
	int client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket_fd < 0) {
		perror("Can't start client socket");
	} else {
		LOG_INFO("Client socket creater: %d", client_socket_fd);
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);

	/*
     * Convert servers char address to
     * IPv4 Address
     */
	if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) != 1) {
		perror("Address not suppoerted");
	}

	/*
     * Connect to the server socket
     */
	if ((connect(client_socket_fd, (const struct sockaddr *)&server_addr,
		     sizeof(server_addr))) < 0) {
		perror("Can't connect to the server socket");
	}
	char *client_request = "this is nexus.c client, hello server";
	send(client_socket_fd, client_request, strlen(client_request), 0);
}

/*
 * Client main
 */

int main()
{
	client_start();
	return 0;
}
