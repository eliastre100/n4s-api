#include <unistd.h>
#include <malloc.h>
#include <types.h>
#include "class/car.h"

void net_car_destruct(car_t *self)
{
  if (self != NULL) {
    if (self->io.in != -1)
      close(self->io.in);
    if (self->io.out != -1)
      close(self->io.out);
    free(self);
  }
}