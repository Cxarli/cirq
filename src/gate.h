#ifndef GATE_H
#define GATE_H


#include "defines.h"
#include "vector.h"
#include "port.h"


typedef struct gate {
  char *name;
  char *type;

  vector_t ports;
} gate_t;


void gate_add_input(gate_t *gate, int i, char name[]);
void gate_add_output(gate_t *gate, int i, char name[]);
void gate_set_ports(gate_t *gate);
void gate_update_state(gate_t *gate);
port_t *gate_get_port_by_name(gate_t *gate, char *name);

void gate_print(gate_t *gate);
void gate_init(gate_t *gate);
void gate_free(gate_t *gate);

#endif
