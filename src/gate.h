#ifndef GATE_H
#define GATE_H


#include "defines.h"
#include "vector.h"
#include "port.h"


// Forward declaration
typedef struct circuit circuit_t;


typedef struct gate {
  char *name;
  char *type;

  vector_t ports;
} gate_t;


void gate_add_port(gate_t *gate, unsigned int i, char *X_name, PortType_t type);
void gate_add_input(gate_t *gate, unsigned int i, char *name);
void gate_add_output(gate_t *gate, unsigned int i, char *name);
bool gate_set_ports(gate_t *gate, vector_t *dependencies);
void gate_take_gates_from_circuit(gate_t *gate, circuit_t *circuit);
void gate_update_state(gate_t *gate);
port_t *gate_get_port_by_name(gate_t *gate, char *name);

void gate_print(gate_t *gate);
void gate_init(gate_t *gate);
void gate_free(gate_t *gate);

#endif
