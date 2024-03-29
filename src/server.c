#include "../include/server.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

// server main

void server_start()
{
	/*
	 * AF_INET = ip domain
	 * SOCK_STREAM = TCP
	 * 0 = protocol identifier(ip) 
	 */
	int server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sockaddr;

	int option = 1;
	setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &option,
		   sizeof(option));

	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(PORT);
	sockaddr.sin_addr.s_addr = INADDR_ANY;

	socklen_t addr_len = sizeof(sockaddr);

	if (server_socket_fd < 0) {
		perror("Can't establish the server socket");
	}
	if (bind(server_socket_fd, (const struct sockaddr *)&sockaddr,
		 sizeof(sockaddr)) < 0) {
		perror("Can't bind the server socket");
		exit(1);
	} else {
		LOG_INFO("Server bind port: %d", ntohs(sockaddr.sin_port));
		LOG_INFO("Server bind address: %d", sockaddr.sin_addr.s_addr);
	}

	/*
     * Set the socket to passive(server) one
     * that LISTENS the coming connections
     */
	if (listen(server_socket_fd, MAX_SERVER_BACKLOG) < 0) {
		perror("The server socket cannot listen incoming connections");
	} else {
		LOG_OK("Server socket is in listening mode %d",
		       server_socket_fd);
	}

	while (1) {
		int new_connection_on_socket = 0;
		if ((new_connection_on_socket = accept(
			     server_socket_fd, (struct sockaddr *)&sockaddr,
			     &addr_len)) < 0) {
			perror("Server can't accept new connection");
		}

		/*
     * Read from the coming connection
     * save to buffer
     */
		char server_read_buffer[MAX_SOCKET_BUFFER_LEN];

		memset(server_read_buffer, 0, MAX_SOCKET_BUFFER_LEN);
		int read_status = read(new_connection_on_socket,
				       server_read_buffer,
				       (MAX_SOCKET_BUFFER_LEN - 1));
		LOG_INFO("Read status from client connection %d", read_status);
		LOG_OK("CLIENT REQUEST:\n%s\n", server_read_buffer);

		request_type_t request_header =
			request_method_type(server_read_buffer);

		LOG_INFO("Method Header: %d", request_header);

		if (request_header == GET) {
			char *requested_file =
				request_get_requested_file(server_read_buffer);

			char *server_get_response =
				response_get(requested_file);

			LOG_INFO("Requested File :%s", requested_file);
			send(new_connection_on_socket, server_get_response,
			     strlen(server_get_response), 0);
		}

		close(new_connection_on_socket);
	}
	close(server_socket_fd);
}

void print_server_banner()
{
	FILE *banner_fp = fopen("static_content/banner.txt", "r");

	if (banner_fp == NULL) {
		perror("Can't open server banner file");
	}
	char c;
	printf("\n");
	while ((c = fgetc(banner_fp)) != EOF) {
		printf("%c", c);
	}
	printf("\n");
	fclose(banner_fp);
}

int main()
{
	print_server_banner();
	server_start();
	return 0;
}
