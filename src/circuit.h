#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <stdlib.h>

#include "defines.h"
#include "gate.h"
#include "wire.h"


struct circuit {
  char name[BUF_SIZE];
  size_t amount_gates;
  struct gate gates[BUF_SIZE];
  size_t amount_wires;
  struct wire wires[BUF_SIZE];
};

void print_circuit(struct circuit *circ);

#endif
