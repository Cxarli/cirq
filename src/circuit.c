#include <stdio.h>

#include "circuit.h"


void print_circuit(struct circuit *circ) {
  printf("Circuit %s:\n", circ->name);
  printf("%lu gates, %lu wires\n", circ->amount_gates, circ->amount_wires);

  char str[BUF_SIZE];

  printf("\n");
  for (unsigned int i = 0; i < circ->amount_gates; i++) {
    gate_to_string(&circ->gates[i], str);
    printf("gate %u: %s\n", i, str);
  }

  printf("\n");
  for (unsigned int i = 0; i < circ->amount_wires; i++) {
    wire_to_string(&circ->wires[i], str);
    printf("wire %u: %s\n", i, str);
  }
}
