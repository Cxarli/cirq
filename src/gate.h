#ifndef GATE_H
#define GATE_H

#include <stdlib.h>

#include "defines.h"
#include "port.h"


struct gate {
  char name[BUF_SIZE];
  char type[BUF_SIZE];

  size_t amount_ports;
  struct port *ports[BUF_SIZE];
};

void gate_to_string(struct gate *gate, char *str);

#endif
