#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#define fail_if(cond,msg) \
  if (cond) {	          \
    perror(msg);          \
    exit(1);              \
  }

int main(int argc, char **argv) {
  u_short port = 9999;

  char buff[512];
  int res;

  int master = socket(AF_INET, SOCK_STREAM, 0);
  fail_if( master<0, "Server: error socket");

  int on = 1;
  res = setsockopt(master, SOL_SOCKET,
	      SO_REUSEADDR, &on, sizeof(on));
  fail_if(res<0, "Server: error setsockopt");

#ifdef SO_REUSEPORT	
  res = setsockopt(master, SOL_SOCKET,
	      SO_REUSEPORT, &on, sizeof(on));
  fail_if(res<0, "Server: error setsockopt");
#endif
  
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  res = bind(master,
	     (struct sockaddr *) &serv_addr,
	     sizeof(struct sockaddr_in));
  fail_if(res<0, "Server: error bind");

  
  res = listen(master, SOMAXCONN);
  fail_if(res<0, "Server: error listen");

  
  fprintf(stderr, "Server ready\n");
  
  int clilen = sizeof(struct sockaddr_in);
  struct sockaddr_in cli_addr;
  int client_socket =
    accept(master,
	   (struct sockaddr *) &cli_addr,
	   (socklen_t *) & clilen);
  fail_if(client_socket < 0,
	  "Server: error accept");

  res = recv(client_socket, buff, 511, 0);
  fail_if(res <0, "Server: recv() failed");

  buff[res] = '\0';
  printf("Got '%s'\n", buff);
  
  shutdown(client_socket, SHUT_RDWR);
  close(client_socket);  
  return 0;
}
