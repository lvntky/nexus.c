#include "../include/request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int request_method_type(char *buffer)
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

//TODO: Refactor needed
char *request_get_requested_file(char *buffer)
{
	int start_offset = 0;
	int end_offset = 0;
	for (int i = 0; buffer[i] != '/'; i++) {
		start_offset++;
	}
	for (int j = start_offset; buffer[j] != ' '; j++) {
		end_offset++;
	}
	char *req_file_name = (char *)malloc(end_offset);
	strncpy(req_file_name, buffer + start_offset, end_offset);
	req_file_name[end_offset] = '\0';

	return req_file_name;
}
