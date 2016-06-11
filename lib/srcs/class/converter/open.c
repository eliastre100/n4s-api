#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <types.h>
#include "class/converter.h"

bool converter_open(converter_t *self, const char *path)
{
  if (self->bmp_fd != -1)
    self->close(self);
  if ((self->bmp_fd = open(path, O_RDONLY)) == -1) {
    perror("converter");
    return (false);
  }
  if (read(self->bmp_fd, &self->bmp_header, sizeof(self->bmp_header)) < sizeof(self->bmp_header) ||
      self->bmp_header.type != 'B' + ('M' << 8)) {
    fprintf(stderr, "converter: Invalid bmp file %s\n", path);
    return (false);
  }
  if (read(self->bmp_fd, &self->bmp_info, sizeof(self->bmp_info)) != sizeof(self->bmp_info))
    fprintf(stderr, "converted: WARNING: unable to read valid bmp info, map may be corrupted\n");
  if (self->bmp_info.bpx != 24) {
    fprintf(stderr, "converter: ERROR: Have %dbpp, only 24bpp is supported\n", self->bmp_info.bpx);
    return (false);
  }
  if (self->bmp_info.compression != 0) {
    fprintf(stderr, "converter: ERROR: Have compression type %d but no compression is supported\n", self->bmp_info.compression);
    return (false);
  }
  if (self->bmp_info.width * self->bmp_info.height * 3 != self->bmp_info.size) {
    fprintf(stderr, "converter: ERROR: have conflicting size informations (width %d, height %d and size %d)\n", self->bmp_info.width, self->bmp_info.height, self->bmp_info.size);
    return (false);
  }
  return (true);
}