#include <unistd.h>
#include <stdio.h>
#include <types.h>
#include "config.h"
#include "utils.h"
#include "class/command.h"
#include "class/car.h"

bool net_command_import(command_t *self, io_t *io)
{
  int fd;

  fd = IN_IO(io);
  if (read(fd, &self->data, sizeof(self->data)) < sizeof(self->data))
    return (false);
  else
    return (true);
}