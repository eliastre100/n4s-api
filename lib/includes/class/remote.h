#ifndef N4S_API_REMOTE_H_
# define N4S_API_REMOTE_H_

#include "config.h"
#include "types.h"

struct remote {
  /* User usefull attributs */
  char name[NAME_LENGTH];
  uint32_t speed;
  uint32_t wheels;

  /* Lib attributes */
  io_t io;

  /* Methods */
  void (*destruct)(remote_t *self);
  bool (*connect)(remote_t *self, const char *host,uint16_t port);
};

remote_t *new_net_remote(char *name);
void net_remote_destruct(remote_t *self);
bool net_remote_connect(remote_t *self, const char *host,uint16_t port);

#endif /* !N4S_API_REMOTE_H_ */
