#!/bin/sh

gcc -Wall -Wextra -Werror -pedantic ./client_tcp/client.c -o  ./bin/client
./bin/client
