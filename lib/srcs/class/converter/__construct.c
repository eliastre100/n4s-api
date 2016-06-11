#include <malloc.h>
#include <fcntl.h>
#include <strings.h>
#include "class/converter.h"

static void converter_methods(converter_t *self)
{
  self->open = converter_open;
  self->close = converter_close;
  self->import_pixels = converter_import_pixels;
  self->search_start = converter_search_start;
  self->max_checkpoint = converter_max_checkpoint;
  self->export_header = converter_export_header;
  self->export_map = converter_export_map;
  self->export = converter_export;
  self->destruct = converter_destruct;
}

converter_t *new_converter()
{
  converter_t *self;

  if ((self = malloc(sizeof(converter_t))) == NULL)
    return (NULL);
  converter_methods(self);
  self->bmp_fd = -1;
  self->pixels = NULL;
  return (self);
}