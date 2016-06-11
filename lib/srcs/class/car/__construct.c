#include <malloc.h>
#include <types.h>
#include <unistd.h>
#include "class/car.h"
#include "class/command.h"

static void net_car_methods(car_t *self)
{
  self->listen = car_listen;
  self->destruct = net_car_destruct;
}

car_t *new_net_car(int sock)
{
  car_t *self;

  if ((self = malloc(sizeof(car_t))) == NULL)
    return (NULL);
  net_car_methods(self);
  if ((self->command = new_net_command()) == NULL) {
    self->destruct(self);
    return (NULL);
  }
  if (read(sock, self->name, NAME_LENGTH) == -1) {
    fprintf(stderr, "New car: Unable to get name from remote\n");
    self->destruct(self);
    return (NULL);
  }
  self->wheels = 0;
  self->speed = 0;
  self->io.in = -1;
  self->io.out = sock;
  self->io.same = true;
  self->pos.x = 0;
  self->pos.y = 0;
  self->enable = true;
  self->running = false;
  return (self);
}