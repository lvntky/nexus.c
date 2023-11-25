#include "../include/tcp.h"

int tcp_establish_server_connection()
{
	// AF_INET = ip domain
	// SOCK_STREAM = TCP
	// 0 = protocol identifier(ip)
	int server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sockaddr;

    sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = PORT;
	sockaddr.sin_addr.s_addr = INADDR_ANY;

	if (server_socket_fd < 0) {
		perror("Can't establish the server socket");
		return -1;
	}
	if (bind(server_socket_fd, (const struct sockaddr *)&sockaddr,
		 sizeof(sockaddr)) < 0) {
		perror("Can't bind the server socket");
	}

	return server_socket_fd;
}
