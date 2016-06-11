#include <unistd.h>
#include "types.h"

bool close_io(io_t *io)
{
  if (io->in != -1) {
    close(io->in);
    io->in = -1;
  }
  if (io->out != -1) {
    close(io->out);
    io->out = -1;
  }
  return (true);
}