#include <stdio.h>
#include <types.h>
#include "class/converter.h"

pos_t converter_search_start(converter_t *self)
{
  rgb_t *color;
  pos_t pos;
  unsigned int i = 0;

  for (i = 0; i < self->bmp_info.width * self->bmp_info.height; i++) {
    color = &self->pixels[i];
    if (color->red == 0 && color->green == 255 && color->blue == 0) {
      break;
    }
  }
  pos.x = i % self->bmp_info.width;
  pos.y = self->bmp_info.height - i / self->bmp_info.height - 1;
  return (pos);
}

unsigned char converter_max_checkpoint(converter_t *self, unsigned char start)
{
  unsigned int i = 0;
  rgb_t *color;


  if (start == 255)
    return (255);
  for (i = 0; i < self->bmp_info.width * self->bmp_info.height; i++) {
    color = &self->pixels[i];
    if (color->red == start && color->green == start && color->blue == start) {
      return (self->max_checkpoint(self, start + 1));
    }
  }
  return (start - 1);
}