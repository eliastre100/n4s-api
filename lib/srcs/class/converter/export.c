#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <types.h>
#include "config.h"
#include "class/converter.h"

bool converter_export_header(converter_t *self, float start_angle, int fd)
{
  self->n4s_header.angle_start = start_angle;
  self->n4s_header.height = self->bmp_info.height;
  self->n4s_header.width = self->bmp_info.width;
  self->n4s_header.nb_checkpoint = self->max_checkpoint(self, 1);
  self->n4s_header.start_pos = self->search_start(self);
  self->n4s_header.magic = MAGIC;
  self->n4s_header.size = sizeof(self->n4s_header) + sizeof(uint16_t) * self->n4s_header.width * self->n4s_header.height;
  if (write(fd, &self->n4s_header, sizeof(self->n4s_header)))
    return (true);
  else
    return (false);
}

bool converter_export_map(converter_t *self, int fd)
{
  int x = 0;
  int y = self->n4s_header.height - 1;
  rgb_t *color;
  uint16_t map_value;

  if (self->pixels == NULL) {
    fprintf(stderr, "converter: ERROR: No pixels have been imported before exporting map !\n");
    return (false);
  }
  while (y >= 0) {
    x = 0;
    while (x < self->n4s_header.width) {
      color = &self->pixels[x + y * self->n4s_header.width];
      if (color->red == 0 && color->blue == 0 && color->green == 0)
	map_value = 0;
      else if (color->red == color->green && color->green == color->blue)
	map_value = color->red;
      else if (color->green == 255)
	map_value = 256;
      else if (color->blue == 255)
	map_value = 257;
      else
	fprintf(stderr, "converter: WARNING: invalid pixel detected at (%d;%d) (Map may be corrupted)\n", x, self->n4s_header.height - y);
      write(fd, &map_value, sizeof(map_value));
      x++;
    }
    y--;
  }
  return (true);
}

bool converter_export(converter_t *self, const char *path, float start_angle)
{
  int fd;
  bool status;

  if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
    perror("converter");
    return (false);
  }
  if (self->import_pixels(self) && self->export_header(self, start_angle, fd) && self->export_map(self, fd))
    status = true;
  else
    status = false;
  close(fd);
  return (status);
}