#include <malloc.h>
#include <types.h>
#include <unistd.h>
#include <strings.h>
#include "class/converter.h"

bool converter_import_pixels(converter_t *self)
{
  if (self->pixels != NULL)
    free(self->pixels);
  if (self->bmp_fd == -1) {
    fprintf(stderr, "converter: ERROR: need to load a file before importing pixels !\n");
    return (false);
  }
  lseek(self->bmp_fd, self->bmp_header.offset, SEEK_SET);
  if ((self->pixels = malloc(self->bmp_info.size)) == NULL)
    return (false);
  bzero(self->pixels, self->bmp_info.size);
  if (read(self->bmp_fd, self->pixels, self->bmp_info.size) != self->bmp_info.size)
    fprintf(stderr, "Unable to read all expected pixels. (Map may be corrupted)\n");
  return (true);
}
