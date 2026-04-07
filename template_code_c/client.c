#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
  char *IP = "127.0.0.1";
  u_short server_port = 9999;

  int res;
  char *buff = "HELLO";

  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    perror("Client: socket() failed");
    exit(1);
  }
  
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  
  addr.sin_family = AF_INET;
  addr.sin_port = htons(server_port);
  inet_pton(AF_INET, IP, &addr.sin_addr);

  res = connect(fd,
                (struct sockaddr *) &addr,
		sizeof(addr));
  if (res < 0) {
    fprintf(stderr, "Cannot connect: %s\n",
	    strerror(errno));
    exit(1);
  }

  // send(fd, buffer, strlen(buffer), 0);
  int todo = strlen(buff);
  char *p = buff;
  while (todo>0) {
    int res = send(fd, p, todo, 0);
    if (res == -1) {
      perror("Client: cannot send message");
      exit(1);
    }
    p += res;
    todo -= res;
  }

  shutdown(fd, SHUT_RDWR);
  close(fd);
  return 0;
}
