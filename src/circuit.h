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


void circuit_print(circuit_t *circ);

void circuit_init(circuit_t *circ);

#endif
