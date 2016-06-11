#ifndef N4S_API_COMMAND_H_
# define N4S_API_COMMAND_H_

#include "types.h"

struct command_data {
  uint32_t command;
  float value;
};

struct command {
  struct command_data data;

  bool (*set_value)(command_t *self, float value);
  bool (*load)(command_t *self, command_e command);
  bool (*send)(command_t *self, io_t *io);
  bool (*import)(command_t *self, io_t *io);
  bool (*apply)(command_t *self, car_t *car);
  void (*destruct)(command_t *self);
};

command_t *new_net_command();
void net_command_destruct(command_t *self);
bool command_set_value(command_t *self, float value);
bool net_command_load(command_t *self, command_e command);
bool net_command_send(command_t *self, io_t *io);
bool net_command_import(command_t *self, io_t *io);
bool command_apply(command_t *self, car_t *car);

#endif /* !N4S_API_COMMAND_H_ */
