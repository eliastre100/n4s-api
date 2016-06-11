#include <malloc.h>
#include "class/command.h"

static void net_command_methods(command_t *self)
{
  self->set_value = command_set_value;
  self->load = net_command_load;
  self->send = net_command_send;
  self->import = net_command_import;
  self->apply = command_apply;
  self->destruct = net_command_destruct;
}

command_t *new_net_command()
{
  command_t *self;

  if ((self = calloc(sizeof(command_t), 1)) == NULL)
    return (NULL);
  net_command_methods(self);
  self->data.command = NONE;
  self->data.command = 0;
  return (self);
}