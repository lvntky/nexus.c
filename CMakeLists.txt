cmake_minimum_required(VERSION 3.26)
project(nexus)

set(SOURCE_FILES ./src/tcp_client.c ./src/tcp_server.c ./include/config.h)

add_executable(nexus ${SOURCE_FILES})
