#include <unistd.h>
#include "class/command.h"

bool net_command_send(command_t *self, io_t *io)
{
  if (self->data.command == NONE)
    return (true);
  if (write(io->out, &self->data, sizeof(self->data)) > 0)
    return (true);
  else
    return (false);
}