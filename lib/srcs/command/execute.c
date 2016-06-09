#include <stdio.h>
#include "command.h"
#include "class/car.h"

bool command_start_simulation(car_t *car, float parameter)
{
  (void)parameter;
  printf("%s asked to start his simulation\n", "toto");
  if (car->running == true)
    return (false);
  else {
    car->running = true;
    return (true);
  }
}