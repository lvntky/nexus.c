#ifndef _REQUEST_H_
#define _REQUEST_H_

#define MAX_REQUEST_METHOD_HEADER_LEN 5

#include "request_type.h"

int request_get_type(char *);

#endif