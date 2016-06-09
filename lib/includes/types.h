#ifndef N4S_API_TYPES_H_
# define N4S_API_TYPES_H_

#include <stdint.h>
#include <stdbool.h>

/* class */
typedef struct command command_t;
typedef struct car car_t;
typedef struct listener listener_t;
typedef struct remote remote_t;

typedef struct {
  uint32_t x;
  uint32_t y;
} pos_t;

typedef struct {
  char name[200];
  pos_t pos;
} net_car_t;

typedef struct {
  uint32_t command;
  float value;
} net_command_t;

typedef struct {
  int in;
  int out;
  bool same;
} io_t;

#endif /* !N4S_API_TYPES_H_ */
