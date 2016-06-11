#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <memory.h>
#include "class/converter.h"

int main(int argc, char **argv)
{
  converter_t *converter;

  if (argc < 3)
    fprintf(stderr, "Usage: %s {bmp referance path} {start angle}\n", argv[0]);
  else {
    printf("Will convert %s to %s.n4s\n", argv[1], argv[1]);
    if ((converter = new_converter()) != NULL) {
      converter->open(converter, argv[1]);
      strcat(argv[1], ".n4s");
      converter->export(converter, argv[1], atol(argv[2]));
      converter->destruct(converter);
    }
  }
  return (0);
}