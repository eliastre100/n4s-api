#include <malloc.h>
#include <sys/socket.h>
#include <tgmath.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "class/listener.h"
#include "class/car.h"

car_t **net_listener_connect(listener_t *self, unsigned int acceptable)
{
  unsigned int accepted_count = 0;
  int sock;
  struct sockaddr_in csin = { 0 };
  int sinsize = sizeof(csin);

  self->listen(self, false);
  self->disconnect(self);
  printf("Waiting for %d client to connect\n", acceptable);
  if(listen(self->socket, acceptable) == -1) {
    perror("listener");
    return (NULL);
  }
  if ((self->cars = malloc(sizeof(car_t *) * (acceptable + 1))) == NULL)
    return (NULL);
  while (accepted_count < acceptable) {
    sock = accept(self->socket, (struct sockaddr *)&csin, (socklen_t *)&sinsize);
    if(sock == -1)
      perror("listener");
    else {
      self->cars[accepted_count] = new_net_car(sock);
      printf("accepted client from %s [%s]\n", inet_ntoa(csin.sin_addr), self->cars[accepted_count++]->name);
    }
  }
  self->cars[accepted_count] = NULL;
  return (self->cars);
}