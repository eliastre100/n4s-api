#include "class/command.h"

bool command_set_value(command_t *self, float value)
{
  if (value < -1 || value > 1)
    return (false);
  else {
    self->data.value = value;
    return (true);
  }
}