#ifndef WIRE_H
#define WIRE_H

#include "defines.h"


typedef struct wire {
  char *leftuuid;
  char *leftport;
  char *rightuuid;
  char *rightport;
} wire_t;

void print_wire(wire_t *wire);

#endif
