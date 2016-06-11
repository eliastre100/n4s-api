#include <malloc.h>
#include "class/command.h"

void net_command_destruct(command_t *self)
{
  if (self != NULL) {
    free(self);
  }
}