#ifndef N4S_API_TYPES_H_
# define N4S_API_TYPES_H_

#include <stdint.h>
#include <stdbool.h>

/* class */
typedef struct command command_t;
typedef struct car car_t;
typedef struct listener listener_t;
typedef struct remote remote_t;
typedef struct command command_t;
typedef struct converter converter_t;

typedef struct {
  uint32_t command;
  float value;
} net_command_t;

typedef struct {
  int in;
  int out;
  bool same;
} io_t;

#pragma pack(push)
#pragma pack(1)

typedef struct {
  uint32_t x;
  uint32_t y;
} pos_t;

typedef struct {
  uint16_t type;
  uint32_t size;
  uint32_t reserved;
  uint32_t offset;
} bmp_header_t;

typedef struct {
  uint32_t header_size;
  uint32_t width;
  uint32_t height;
  uint16_t planes;
  uint16_t bpx;
  uint32_t compression;
  uint32_t size;
  uint32_t xppm, yppm;
  uint32_t colors;
  uint32_t imp_colors;
} bmp_info_t;

typedef struct {
  unsigned char blue;
  unsigned char green;
  unsigned char red;
} rgb_t;

typedef struct {
  uint32_t width;
  uint32_t height;
  uint32_t magic;
  uint32_t size;
  pos_t start_pos;
  float angle_start;
  unsigned char nb_checkpoint;
} n4s_header_t;

#pragma pack(pop)

typedef struct {
  char name[200];
  pos_t pos;
} net_car_t;

typedef enum {
  START,
  FORWARD,
  NONE
} command_e;

#endif /* !N4S_API_TYPES_H_ */
