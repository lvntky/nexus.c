#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include "clogger.h"

/*
 * response headers
 */
#define HEADER_PREFIX_OK "HTTP/1.1 200 OK\n"
#define CONTENT_TYPE "Content-Type: "
#define SERVER "Server: "

char *response_get(char *);
char *response_prepare();

#endif