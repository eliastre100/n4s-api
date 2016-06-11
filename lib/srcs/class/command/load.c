#include <netinet/in.h>
#include "class/command.h"

bool net_command_load(command_t *self, command_e command)
{
  if (command < 0 || command >= NONE)
    return (false);
  else {
    self->data.command = htonl(command);
    return (true);
  }
}