#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include "command.h"

static void command_std_methods(command_t *self)
{
  self->set_value = command_set_value;
  self->load = command_load;
  self->prepare = std_command_prepare;
  self->send = std_command_send;
  self->destruct = std_command_destruct;
}

command_t *new_std_command()
{
  command_t *self;

  if ((self = malloc(sizeof(command_t))) == NULL)
  {
    fprintf(stderr, "Unable to allocate memory for command\n");
    return (NULL);
  }
  self->fd_in = 0;
  self->fd_out = 1;
  self->selected = NONE;
  self->value = 0;
  command_std_methods(self);
  return (self);
}

static int net_connect(struct hostent *host, uint16_t port)
{
  int sock;
  struct sockaddr_in sin = { 0 };

  if (host == NULL) {
    fprintf (stderr, "new_net_command: Unknown host\n");
    return (-1);
  }
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("new_net_command");
    return (-1);
  }
  sin.sin_addr = *(struct in_addr *) host->h_addr;
  sin.sin_port = htons(port);
  sin.sin_family = AF_INET;
  if(connect(sock,(struct sockaddr *) &sin, sizeof(struct sockaddr)) == -1)
  {
    perror("new_net_command");
    close(sock);
    return (-1);
  }
  return (sock);
}

static void net_command_methods(command_t *self)
{
  self->send = net_command_send;
  self->prepare = net_command_prepare;
  self->destruct = net_command_destruct;
}

command_t *new_net_command(const char *host, uint16_t port)
{
  command_t *self;

  if ((self = new_std_command()) == NULL)
    return (NULL);
  if ((self->fd_out = net_connect(gethostbyname(host), port)) == -1) {
    self->destruct(self);
    return (NULL);
  }
  /*write(self->fd_out, name, 255);*/
  self->fd_in = self->fd_out;
  net_command_methods(self);
  return (self);
}