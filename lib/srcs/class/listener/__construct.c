#include <malloc.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "class/listener.h"

static void net_listener_methods(listener_t *self)
{
  self->listen = net_listener_listen;
  self->destruct = net_listener_destruct;
}

static int net_init(uint16_t port)
{
  int sock;
  struct sockaddr_in sin = { 0 };

  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1 || bind(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1) {
    perror("new_net_listener");
    return (-1);
  }
  return (sock);
}

listener_t *new_net_listener(uint16_t port)
{
  listener_t *self;

  if ((self = malloc(sizeof(listener_t))) == NULL)
    return (NULL);
  net_listener_methods(self);
  if ((self->socket = net_init(port)) == -1) {
    self->destruct(self);
    return (NULL);
  }
  return (self);
}