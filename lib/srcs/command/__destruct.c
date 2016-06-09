#include <malloc.h>
#include <unistd.h>
#include "command.h"

void std_command_destruct(command_t *self)
{
  if (self != NULL) {
    free(self);
  }
}

void net_command_destruct(command_t *self)
{
  if (self != NULL) {
    if (self->fd_out != -1)
      close(self->fd_out);
    free(self);
  }
}