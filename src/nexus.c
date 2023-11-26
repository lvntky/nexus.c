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
	FILE *bannerfp =
		fopen("/home/levent/Projects/nexus.c/static_content", "r");

	char banner_line[MAX_BANNER_LEN];
	while (fgets(banner_line, sizeof(banner_line), bannerfp) != NULL) {
		printf("%s", banner_line);
	}
	fclose(bannerfp);
}
