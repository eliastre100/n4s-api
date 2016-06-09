#ifndef N4S_API_LISTENER_H_
# define N4S_API_LISTENER_H_

#include "car.h"
#include "types.h"

struct listener {
  int socket;
  car_t **(*listen)(listener_t *self, unsigned int acceptable);
  void (*destruct)(listener_t *self);
};

listener_t *new_net_listener(uint16_t port);
void net_listener_destruct(listener_t *self);
car_t **net_listener_listen(listener_t *self, unsigned int acceptable);

#endif /* !N4S_API_LISTENER_H_ */
