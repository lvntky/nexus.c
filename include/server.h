#ifndef _SERVER_H_
#define _SERVER_H_

#define MAX_SERVER_BACKLOG 8
#define MAX_SOCKET_BUFFER_LEN 2048

#include <sys/socket.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "config.h"

void server_start();

#endif
