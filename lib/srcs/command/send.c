#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <command.h>
#include "command.h"

bool std_command_send(command_t *self)
{
  char *command;

  if (self->selected == NONE)
    return (true);
  if ((command = self->prepare(self)) == NULL)
    return (false);
  write(self->fd_out, command, strlen(command));
  free(command);
  return (true);
}

bool net_command_send(command_t *self)
{
  net_command_t *data;

  if (self->selected == NONE)
    return (true);
  if ((data = self->prepare(self)) == NULL)
    return (false);
  write(self->fd_out, data, sizeof(data));
  free(data);
  return (true);
}