#include <stdio.h>
#include "class/command.h"
#include "class/car.h"
#include "utils.h"

bool car_listen(car_t *self)
{
  if (self->command->import(self->command, &self->io))
    return (self->command->apply(self->command, self));
  else {
    close_io(&self->io);
    printf("[%s] Disconnected\n", self->name);
    return (false);
  }
}