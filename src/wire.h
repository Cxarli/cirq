#ifndef WIRE_H
#define WIRE_H

#include "defines.h"

struct wire {
  char leftuuid[BUF_SIZE];
  char leftport[BUF_SIZE];
  char rightuuid[BUF_SIZE];
  char rightport[BUF_SIZE];
};


void wire_to_string(struct wire *wire, char *str);

#endif
