#ifndef GATE_H
#define GATE_H


#include "defines.h"
#include "vector.h"


typedef struct gate {
  char *name;
  char *type;

  vector_t ports;
} gate_t;


void gate_print(gate_t *gate);

void gate_init(gate_t *gate);
void gate_free(gate_t *gate);

#endif
