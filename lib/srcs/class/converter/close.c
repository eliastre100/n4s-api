#include <unistd.h>
#include "class/converter.h"

bool converter_close(converter_t *self)
{
  if (self->bmp_fd != -1)
    close(self->bmp_fd);
  return (true);
}