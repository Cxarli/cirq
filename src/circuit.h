#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <stdlib.h>

#include "defines.h"
#include "vector.h"


typedef struct circuit {
  char name[BUF_SIZE];

  vector_t gates;
  vector_t wires;
} circuit_t;


void print_circuit(circuit_t *circ);

#endif
