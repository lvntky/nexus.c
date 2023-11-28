#include "../include/response.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
		total_path = "static_content/index.html";
	}
	FILE *index_fp = fopen(total_path, "rb");
	LOG_ERROR("FULL PATH: %s", total_path);
	if (index_fp == NULL) {
		// Handle file not found or other errors
		return NULL;
	}

	fseek(index_fp, 0, SEEK_END);
	long index_size = ftell(index_fp);
	rewind(index_fp);

	response_data = malloc(index_size + 1); // Add 1 for null terminator
	if (response_data == NULL) {
		// Handle memory allocation error
		fclose(index_fp);
		return NULL;
	}

	fread(response_data, index_size, 1, index_fp);
	response_data[index_size] = '\0'; // Null-terminate the string

	fclose(index_fp);

	// Add Content-Type header for HTML
	char *html_response =
		malloc(index_size + 100); // Allocate extra space for headers
	if (html_response == NULL) {
		// Handle memory allocation error
		free(response_data);
		return NULL;
	}

	char *content_type;
	char *extension = get_filename_ext(requested_file);
	if (strcmp(extension, "jpg") == 0) {
		content_type = "image/jpeg";
	} else {
		content_type = "text/html";
	}

	sprintf(html_response, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n%s",
		content_type, response_data);

	free(response_data);

	return html_response;
}
