#include <stdio.h>
#include "../include/nexus.h"

int main()
{
	nexus_banner_print();
	int tcp_server_socket = tcp_establish_server_connection();
	if (tcp_server_socket) {
	}
	return 0;
}

void nexus_banner_print()
{
	FILE *banner_fp = fopen("static_content/banner.txt", "r");
	if (banner_fp == NULL) {
		perror("Error opening file");
		return;
	}
	char c;
	while ((c = fgetc(banner_fp)) != EOF) {
		putchar(c);
	}

	fclose(banner_fp);
}