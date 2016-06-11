#ifndef N4S_API_CONVERTER_H_
# define N4S_API_CONVERTER_H_

#include "types.h"

struct converter {
  int bmp_fd;
  bmp_header_t bmp_header;
  bmp_info_t bmp_info;
  n4s_header_t n4s_header;
  rgb_t *pixels;

  bool (*open)(converter_t *self, const char *path);
  bool (*close)(converter_t *self);
  bool (*import_pixels)(converter_t *self);
  pos_t (*search_start)(converter_t *self);
  unsigned char (*max_checkpoint)(converter_t *self, unsigned char start);
  bool (*export_header)(converter_t *self, float start_angle, int fd);
  bool (*export_map)(converter_t *self, int fd);
  bool (*export)(converter_t *self, const char *path, float start_angle);
  void (*destruct)(converter_t *self);
};

converter_t *new_converter();
void converter_destruct(converter_t *self);
bool converter_close(converter_t *self);
bool converter_open(converter_t *self, const char *path);
bool converter_import_pixels(converter_t *self);
bool converter_export_header(converter_t *self, float start_angle, int fd);
bool converter_export_map(converter_t *self, int fd);
bool converter_export(converter_t *self, const char *path, float start_angle);
unsigned char converter_max_checkpoint(converter_t *self, unsigned char start);
pos_t converter_search_start(converter_t *self);

#endif /* !N4S_API_CONVERTER_H_ */
