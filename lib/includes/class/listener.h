#ifndef N4S_API_LISTENER_H_
# define N4S_API_LISTENER_H_

#include <pthread.h>
#include "class/car.h"
#include "types.h"

struct listener {
  int socket;
  pthread_t thread;
  car_t **cars;
  bool listening;

  car_t **(*connect)(listener_t *self, unsigned int acceptable);
  bool (*disconnect)(listener_t *self);
  bool (*listen)(listener_t *self, bool listen);
  void (*destruct)(listener_t *self);
};

listener_t *new_net_listener(uint16_t port);
void net_listener_destruct(listener_t *self);
car_t **net_listener_connect(listener_t *self, unsigned int acceptable);
bool net_listener_listen(listener_t *self, bool listen);
bool net_listener_disconnect(listener_t *self);

#endif /* !N4S_API_LISTENER_H_ */
