#include <malloc.h>
#include <unistd.h>
#include "class/remote.h"
#include "class/command.h"

void net_remote_destruct(remote_t *self)
{
  if (self != NULL) {
    if (self->io.out != -1)
      close(self->io.out);
    if (self->io.in != -1)
      close(self->io.in);
    if (self->command != NULL)
      self->command->destruct(self->command);
    free(self);
  }
}