#include "command.h"

bool command_set_value(command_t *self, float value)
{
  if (value < MIN_VALUE || value > MAX_VALUE)
    return (false);
  else {
    self->value = value;
    return (true);
  }
}