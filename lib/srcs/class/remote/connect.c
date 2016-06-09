#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <types.h>
#include "class/remote.h"

static int net_connect(struct hostent *host, uint16_t port)
{
  int sock;
  struct sockaddr_in params = { 0 };

  if (host == NULL)
    return (-1);
  params.sin_addr = *(struct in_addr *) host->h_addr;
  params.sin_port = htons(port);
  params.sin_family = AF_INET;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (-1);
  if(connect(sock,(struct sockaddr *) &params, sizeof(struct sockaddr)) == -1) {
    close(sock);
    return (-1);
  }
  return (sock);
}

bool net_remote_connect(remote_t *self, const char *host, uint16_t port)
{
  int sock;

  if (host == NULL) {
    fprintf(stderr, "%s: Invalid host got %s\n", self->name, host);
    return (false);
  }
  if ((sock = net_connect(gethostbyname(host), port)) == -1) {
    perror(self->name);
    return (false);
  }
  self->io.out = sock;
  write(self->io.out, self->name, NAME_LENGTH);
  return (true);
}