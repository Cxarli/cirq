#include <stdio.h>
#include <string.h>

#include "gate.h"
#include "port.h"


void print_gate(gate_t *gate) {
  printf("{ [%s] %s (%lu)}\n", gate->type, gate->name, gate->ports.amount);

  DEBUG;

  for (size_t i = 0; i < gate->ports.amount; i++) {
    port_t *p = gate->ports.items[i];

    DEBUG;

    print_port(p);
    printf("\n");

    DEBUG;
  }
}
