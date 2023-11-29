#include "../include/response.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Assume LOG_ERROR is a macro or function for logging, replace it with your actual logging mechanism

char *get_filename_ext(const char *filename)
{
	char *dot = strrchr(filename, '.');
	if (!dot || dot == filename)
		return "";
	return dot + 1;
}

char *construct_reponse(char *http_response, char *content_type,
			size_t file_size, char *response_data)
{
	sprintf(http_response,
		"HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %zu\r\n\r\n",
		content_type, file_size);

	// Copy binary data into response buffer
	memcpy(http_response + strlen(http_response), response_data, file_size);

	return http_response;
}

char *response_get(char *requested_file)
{
	char *http_response;
	size_t file_size;
	char *response_data;
	char *content_type;

	char *full_file_path = malloc(strlen(requested_file) + 1);

	if (strcmp(requested_file, "favicon.ico") == 0) {
		return NULL;
	}
	if (strcmp(requested_file, "/") == 0) {
		full_file_path = "static_content/index.html";
	} else {
		sprintf(full_file_path, "%s%s", "static_content",
			requested_file);
	}

	if (strcmp(get_filename_ext(requested_file), "jpg") == 0) {
		content_type = malloc(strlen("image/jpg"));
		content_type = "image/jpeg";
	} else {
		content_type = malloc(strlen("text/html"));
		content_type = "text/html";
	}

	FILE *reqfile_fp = fopen(full_file_path, "rb");
	if (reqfile_fp == NULL) {
		return "404 :')";
	}

	fseek(reqfile_fp, 0, SEEK_END);
	file_size = ftell(reqfile_fp);
	rewind(reqfile_fp);

	response_data = malloc(file_size);
	if (response_data == NULL) {
		// Handle memory allocation error
		fclose(reqfile_fp);
		free(full_file_path);
		return NULL;
	}

	// Initialize the buffer to zero to avoid garbage values
	memset(response_data, 0, file_size);

	size_t read_size = fread(response_data, 1, file_size, reqfile_fp);
	if (read_size != file_size) {
		// Handle read error
		fclose(reqfile_fp);
		free(response_data);
		free(full_file_path);
		return NULL;
	}

	fclose(reqfile_fp);
	http_response = malloc(file_size + 256);
	if (http_response == NULL) {
		// Handle memory allocation error
		free(response_data);
		free(full_file_path);
		return NULL;
	}

	LOG_INFO("Content-type: %s", content_type);

	return construct_reponse(http_response, content_type, file_size,
				 response_data);
}
