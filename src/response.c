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

char *response_get(char *requested_file)
{
	if (strcmp(requested_file, "/favicon.ico") == 0) {
		return NULL;
	}

	char *response_data;
	char *total_path = malloc(1024);
	sprintf(total_path, "static_content%s", requested_file);

	if (strcmp(requested_file, "/") == 0) {
		strcpy(total_path, "static_content/index.html");
	}

	FILE *file_fp = fopen(total_path, "rb"); // Open the file in binary mode
	LOG_ERROR("FULL PATH: %s", total_path);
	if (file_fp == NULL) {
		free(total_path);
		return ":( CANT FOUND IT :(";
	}

	fseek(file_fp, 0, SEEK_END);
	size_t file_size = ftell(file_fp);
	rewind(file_fp);

	response_data = malloc(file_size);
	if (response_data == NULL) {
		// Handle memory allocation error
		fclose(file_fp);
		free(total_path);
		return NULL;
	}

	// Initialize the buffer to zero to avoid garbage values
	memset(response_data, 0, file_size);

	size_t read_size = fread(response_data, 1, file_size, file_fp);
	if (read_size != file_size) {
		// Handle read error
		fclose(file_fp);
		free(response_data);
		free(total_path);
		return NULL;
	}

	fclose(file_fp);

	// Print the first few bytes of data for debugging
	LOG_ERROR("First few bytes of data: %02X %02X %02X %02X",
		  (unsigned char)response_data[0],
		  (unsigned char)response_data[1],
		  (unsigned char)response_data[2],
		  (unsigned char)response_data[3]);

	// Construct response
	char *content_type;
	char *extension = get_filename_ext(requested_file);

	if (strcmp(extension, "jpg") == 0 || strcmp(extension, "jpeg") == 0) {
		content_type = "image/jpeg";
	} else {
		content_type = "text/html";
	}

	LOG_ERROR("File Size: %zu", file_size);
	LOG_ERROR("Content Type: %s", content_type);

	// Allocate space for the response, including headers
	char *http_response = malloc(file_size + 200);
	if (http_response == NULL) {
		// Handle memory allocation error
		free(response_data);
		free(total_path);
		return NULL;
	}

	// Construct HTTP headers
	sprintf(http_response, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n",
		content_type);

	// Copy binary data into response buffer
	memcpy(http_response + strlen(http_response), response_data, file_size);

	free(response_data);
	free(total_path);

	return http_response;
}
