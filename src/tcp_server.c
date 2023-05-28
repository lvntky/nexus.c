#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "../include/config.h"
int main (int argc, char** argv)
{
  /*
    Domain: AF_INET(IP)
    Type: SOCK_STREAM - virtual circuit service
    Protocol: 0
   */
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    printf("FAILURE: Can't create TCP socket...");
    return EXIT_FAILURE;
  }

  // Adress the socket with -bind- syscall
  // -bind- Arrange for X events to invoke Tcl scripts
  struct sockaddr_in adress; //netinet
  memset((char*)&adress, 0, sizeof(adress)); // fill the adress space with 0
  /*
    htons: htonl, htons, ntohl, ntohs - convert values between host and network byte order
    Synopsis

    #include <arpa/inet.h>
    uint32_t htonl(uint32_t hostlong);
    uint16_t htons(uint16_t hostshort);
    uint32_t ntohl(uint32_t netlong);
    uint16_t ntohs(uint16_t netshort);
   */
  adress.sin_port = htons(PORT);
  adress.sin_addr.s_addr = htonl(INADDR_ANY);
  adress.sin_family = AF_INET;

  if(bind(server_socket, (struct sockaddr *)&adress, sizeof(adress)) < 0) {
     printf("FAILURE: Can't bind the TCP socket...");
     return  EXIT_FAILURE;
  }
  if (listen(server_socket, 3)) {
    printf("FAILURE: Error occured while listening...");
    return EXIT_FAILURE;
  }
  int new_socket;
  int addrlen = sizeof(adress);
  char *hello_from_server = "Hello from server!";
  while(1) {
    printf("\n========= Waiting For New Connection =========\n\n");
    if((new_socket = accept(server_socket, (struct sockaddr *)&adress, (socklen_t*)&addrlen))<0) {
      printf("FAILURE: Error occured while accepting...");
      return EXIT_FAILURE;
    }
    char buffer[30000] = {0};
    int valread = read( new_socket , buffer, 30000);
    write(new_socket, buffer, 30000);
    printf("\n========= Message Sent =========\n\n");
    close(new_socket);
  }
  return  0;
}
