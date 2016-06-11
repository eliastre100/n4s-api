#include <malloc.h>
#include "class/listener.h"

bool net_listener_disconnect(listener_t *self)
{
  if (self->cars == NULL)
    return (true);
  for (unsigned int i = 0; self->cars[i] != NULL; i++)
    self->cars[i]->destruct(self->cars[i]);
  free(self->cars);
  self->cars = NULL;
  return (true);
}