#include <types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <class/command.h>
#include "class/listener.h"
#include "config.h"

static void *listener_net_loop(void *data)
{
  listener_t *self = data;
  fd_set rdfs;
  int sock_max = 0;
  struct timeval timeout = {0, 0};

  while (1) {
    timeout.tv_usec = 10000;
    FD_ZERO(&rdfs);
    for (unsigned int i = 0; self->cars[i] != NULL; i++) {
      if (IN_IO(&self->cars[i]->io) >= 0) {
	FD_SET(IN_IO(&self->cars[i]->io), &rdfs);
	if (IN_IO(&self->cars[i]->io) > sock_max)
	  sock_max = IN_IO(&self->cars[i]->io);
      }
    }
    if(select(sock_max + 1, &rdfs, NULL, NULL, &timeout) == -1) {
      perror("listener");
      return (NULL);
    }
    for (unsigned int i = 0; self->cars[i] != NULL; i++) {
      if (FD_ISSET(IN_IO(&self->cars[i]->io), &rdfs))
	self->cars[i]->listen(self->cars[i]);
    }
    if (!self->listening)
      return (NULL);
  }
}

bool net_listener_listen(listener_t *self, bool listen)
{
  if (!self->listening && listen) {
    if (pthread_create(&self->thread, NULL, listener_net_loop, self) != -1)
      self->listening = true;
    else
      return (false);
  }
  else if (self->listening && !listen){
    self->listening = false;
    pthread_join(self->thread, NULL);
  }
  return (true);
}