#include "../include/request.h"
#include <string.h>

int request_get_type(char *buffer)
{
	char method_header[MAX_REQUEST_METHOD_HEADER_LEN];
	int i = 0;

	while (buffer[i] != ' ') {
		i++;
	}
	strncpy(method_header, buffer, i);
	method_header[i] = '\0';

	if (strcmp(method_header, "GET") == 0) {
		return 0;
	}
	return 1;
}