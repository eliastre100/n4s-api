#ifndef N4S_API_CAR_H_
# define N4S_API_CAR_H_

#include <stdbool.h>
#include "types.h"
#include "config.h"

struct car {
  char name[NAME_LENGTH];
  float speed;
  float wheels;
  pos_t pos;
  io_t io;
  command_t *command;
  bool running;
  bool enable;

  bool (*listen)(car_t *self);
  void (*destruct)(car_t *self);
};

/* Net car */
car_t *new_net_car(int sock);
void net_car_destruct(car_t *self);

/* General car */
bool car_listen(car_t *self);

#endif /* !N4S_API_CAR_H_ */
