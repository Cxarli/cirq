#ifndef CIRCUIT_H
#define CIRCUIT_H


#include "defines.h"
#include "vector.h"
#include "wire.h"
#include "gate.h"
#include "port.h"


typedef struct circuit {
  char *name;
  vector_t gates;
} circuit_t;


port_t *gate_get_port_by_name(gate_t *gate, char *name);
void circuit_apply_wire(circuit_t *circ, wire_t *wire);

void circuit_print(circuit_t *circ);
void circuit_init(circuit_t *circ);
void circuit_free(circuit_t *circ);

#endif
