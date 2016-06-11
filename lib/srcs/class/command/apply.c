#include <stdio.h>
#include <netinet/in.h>
#include "class/command.h"
#include "class/car.h"

static bool command_forward(command_t *self, car_t *car)
{
  if (!car->running)
    return (false);
  printf("[%s] Set motor speed to %.2f\n", car->name, self->data.value);
  car->speed = self->data.value;
  return (true);
}

static bool command_start(command_t *self, car_t *car)
{
  if (car->running)
    return (false);
  printf("[%s] Start simulation\n", car->name);
  car->running = true;
  return (true);
}

static struct {
  command_e id;
  bool (*run)(command_t *self, car_t *car);
} commands[] = {
  {START, command_start},
  {FORWARD, command_forward},
  {NONE, NULL}
};

bool command_apply(command_t *self, car_t *car)
{
  uint32_t command;

  command = ntohl(self->data.command);
  if (command == NONE)
    return (true);
  else if (command < 0 || command > NONE)
    return (false);
  else
    return (commands[command].run(self, car));
}