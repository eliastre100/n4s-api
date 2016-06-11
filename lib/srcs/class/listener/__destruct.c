#include <malloc.h>
#include <unistd.h>
#include <class/command.h>
#include "class/listener.h"

void net_listener_destruct(listener_t *self)
{
  if (self != NULL)
  {
    self->listen(self, false);
    self->disconnect(self);
    if (self->socket != -1) {
      close(self->socket);
    }
    free(self);
  }
}