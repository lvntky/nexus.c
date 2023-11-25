#include <stdio.h>
#include "../include/nexus.h"

int main()
{
	int tcp_server_socket = tcp_establish_server_connection();
    if(tcp_server_socket) {}
	return 0;
}
