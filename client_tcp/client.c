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
	/*
	 * A mock GET request for test purpose
	 */
	const char *client_request =
		"GET / HTTP/1.1\r\n"
		"Host: localhost:3408\r\n"
		"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:120.0) Gecko/20100101 Firefox/120.0\r\n"
		"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\n"
		"Accept-Language: en-US,en;q=0.5\r\n"
		"Accept-Encoding: gzip, deflate, br\r\n"
		"Connection: keep-alive\r\n"
		"Cookie: Idea-407bbbb9=cfcf2abe-db89-4b13-9f95-f135cc75a96b\r\n"
		"Upgrade-Insecure-Requests: 1\r\n"
		"Sec-Fetch-Dest: document\r\n"
		"Sec-Fetch-Mode: navigate\r\n"
		"Sec-Fetch-Site: none\r\n"
		"Sec-Fetch-User: ?1\r\n\r\n";
	send(client_socket_fd, client_request, strlen(client_request), 0);

	char client_read_buffer[MAX_SOCKET_BUFFER_LEN];
	memset(client_read_buffer, 0, MAX_SOCKET_BUFFER_LEN);
	int client_read_status = read(client_socket_fd, client_read_buffer,
				      (MAX_SOCKET_BUFFER_LEN));
	LOG_INFO("Clint read status: %d", client_read_status);

	// server response
	LOG_INFO("Server response:\n%s\n", client_read_buffer);
	close(client_socket_fd);
}

/*
 * Client main
 */

int main()
{
	client_start();
	return 0;
}
