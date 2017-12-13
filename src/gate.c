#include <stdio.h> // printf

#include "gate.h"

#include "port.h" // port_print, port_t


void gate_print(gate_t *gate) {
  printf("{ %s [%s] (%lu) }", gate->name, gate->type, gate->ports.amount);

  for (size_t i = 0; i < gate->ports.amount; i++) {
    port_t *p = gate->ports.items[i];

    printf("\n\t");
    port_print(p);
  }

  if (gate->ports.amount > 0) {
    printf("\n");
  }
}


void gate_init(gate_t *gate) {
  gate->name = NULL;
  gate->type = NULL;

  vector_init(&gate->ports, BUF_SIZE);
}


void gate_free(gate_t *gate) {
  if (gate->name) free(gate->name);
  if (gate->type) free(gate->type);

  vector_free(&gate->ports);
}
