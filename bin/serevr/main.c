#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <netinet/in.h>
#include <class/command.h>
#include "class/listener.h"

int main()
{
  listener_t *listener;

  listener = new_net_listener(4242);
  if (listener != NULL) {
    listener->connect(listener, 1);
    listener->listen(listener, true);
    sleep(10);
    listener->destruct(listener);
  }
  sleep(1);
  return (0);
}