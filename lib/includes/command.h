#ifndef N4S_API_COMMAND_H_H_
# define N4S_API_COMMAND_H_H_

#include <stdbool.h>
#include "class/car.h"

#ifndef MAX_VALUE
#define MAX_VALUE (1)
#endif

#ifndef MIN_VALUE
#define MIN_VALUE (-1)
#endif

typedef enum {
  START_SIMULATION,
  END_SIMULATION,
  CAR_FORWARD,
  NONE
} command_e;

typedef struct {
  command_e command_id;
  const char *command_str;
  unsigned char param_size;
  bool (*execute)(car_t *car, float parameter);
} command_std_format_t;

struct command{
  int fd_out;
  int fd_in;
  command_e selected;
  float value;
  bool (*set_value)(command_t *self, float value);
  bool (*load)(command_t *self, command_e command);
  bool (*send)(command_t *self);
  void *(*prepare)(command_t *self);
  void (*destruct)(command_t *self);
};

extern command_std_format_t available_cmd[NONE];

/* Std n4s command */
command_t *new_std_command();
void std_command_destruct(command_t *self);
char *std_command_prepare(command_t *self);
bool std_command_send(command_t *self);

/* Common methods */
bool command_set_value(command_t *self, float value);
bool command_load(command_t *self, command_e command);


/* Net n4s methods */
command_t *new_net_command(const char *host, uint16_t port);
void net_command_destruct(command_t *self);
bool net_command_send(command_t *self);
net_command_t *net_command_prepare(command_t *self);

/* command execution */
bool command_start_simulation(car_t *car, float parameter);

#endif /* !N4S_API_COMMAND_H_H_ */
