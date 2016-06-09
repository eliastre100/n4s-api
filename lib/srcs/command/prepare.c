#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <command.h>
#include <netinet/in.h>
#include "command.h"

char *std_command_prepare(command_t *self)
{
  char *command;

  if ((command = strdup(available_cmd[self->selected].command_str)) == NULL)
    return (NULL);
  if (available_cmd[self->selected].param_size > 0) {
    if ((command = realloc(command, sizeof(char) * (strlen(command) + available_cmd[self->selected].param_size + 4))) == NULL) /* TODO: Values can't be greatest than 9.* el invalid write will occur (4 -> 2 ":\0" -> 2 1. */
      return (NULL);
    sprintf(command, "%s:%.*f", command, available_cmd[self->selected].param_size, self->value);
  }
  return (command);
}

net_command_t *net_command_prepare(command_t *self)
{
  net_command_t *data;

  if ((data = malloc(sizeof(net_command_t))) == NULL)
    return (NULL);
  data->command = htonl(self->selected);
  data->value = self->value;
  return (data);
}