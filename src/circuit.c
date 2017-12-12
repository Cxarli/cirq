#include <stdio.h>

#include "circuit.h"
#include "gate.h"
#include "wire.h"


void print_circuit(circuit_t *circ) {
  printf("Circuit %s:\n", circ->name);
  printf("%lu gates, %lu wires\n", circ->gates.amount, circ->wires.amount);

  printf("\n");

  DEBUG;

  for (size_t i = 0; i < circ->gates.amount; i++) {
    printf("gate %lu:\n", i);

    DEBUG;

    print_gate((gate_t*) circ->gates.items[i]);
    printf("\n");

    DEBUG;
  }


  printf("\n");

  DEBUG;

  for (size_t i = 0; i < circ->wires.amount; i++) {
    printf("wire %lu:\n", i);

    DEBUG;

    print_wire((wire_t*) circ->wires.items[i]);
    printf("\n");

    DEBUG;
  }
}
