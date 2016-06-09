#include <malloc.h>
#include <unistd.h>
#include "class/listener.h"

void net_listener_destruct(listener_t *self)
{
  if (self != NULL)
  {
    if (self->socket != -1)
      close(self->socket);
    free(self);
  }
}