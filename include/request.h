#ifndef _REQUEST_H_
#define _REQUEST_H_

#define MAX_REQUEST_METHOD_HEADER_LEN 5
#define MAX_REQUEST_FILE_NAME 1024

#include "request_type.h"
#include "clogger.h"

int request_method_type(char *);
char *request_get_requested_file(char *);

#endif
