#include <unistd.h>
#include <malloc.h>
#include "class/converter.h"

void converter_destruct(converter_t *self)
{
  if (self != NULL) {
    self->close(self);
    if (self->bmp_fd != -1)
      close(self->bmp_fd);
    if (self->pixels != NULL)
      free(self->pixels);
    free(self);
  }
}