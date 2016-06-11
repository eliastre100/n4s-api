#include <stdio.h>
#include <class/command.h>
#include <unistd.h>
#include <types.h>
#include "class/remote.h"

int main(int argc, char **argv)
{
  remote_t *remote;

  if (argc > 1 && (remote = new_net_remote(argv[1])) != NULL) {
    printf("remote %s created\n", remote->name);
    remote->connect(remote, "127.0.0.1", 4242);
    remote->command->load(remote->command, START);
    printf("start %d\n", remote->command->send(remote->command, &remote->io));
    sleep(2);
    remote->command->load(remote->command, FORWARD);
    remote->command->set_value(remote->command, 0.3);
    printf("forward %d\n", remote->command->send(remote->command, &remote->io));
    remote->destruct(remote);
  } else
    fprintf(stderr, "usage: %s {name}\n", argv[0]);
  return (0);
}