#include "command.h"

bool command_load(command_t *self, command_e command)
{
  if (command < 0 || command > NONE)
    return (false);
  else {
    self->selected = command;
    return (true);
  }
}