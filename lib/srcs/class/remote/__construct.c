#include <stdlib.h>
#include <string.h>
#include "class/remote.h"
#include "class/command.h"

static void net_remote_methods(remote_t *self)
{
  self->connect = net_remote_connect;
  self->destruct = net_remote_destruct;
}

remote_t *new_net_remote(char *name)
{
  remote_t *self;

  if ((self = calloc(sizeof(remote_t), 1)) == NULL)
    return (NULL);
  net_remote_methods(self);
  strncpy(self->name, name, NAME_LENGTH);
  if ((self->command = new_net_command()) == NULL) {
    self->destruct(self);
    return (NULL);
  }
  self->io.in = -1;
  self->io.out = -1;
  self->io.same = true;
  return (self);
}