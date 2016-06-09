#include <stdio.h>
#include <command.h>
#include <unistd.h>
#include <malloc.h>
#include <netinet/in.h>
#include "class/listener.h"

int main()
{
  listener_t *listener;
  car_t **cars;
  unsigned int index = 0;

  listener = new_net_listener(4242);
  if (listener != NULL) {
    cars = listener->listen(listener, 1);
    while (cars[index] != NULL) {
      printf("%s is connected\n", cars[index]->name);
      cars[index]->destruct(cars[index]);
      index++;
    }
    free(cars);
    listener->destruct(listener);
  }
  return (0);
}