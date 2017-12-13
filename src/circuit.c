#include <stdio.h> // printf

#include "circuit.h"

#include "gate.h" // gate_print, gate_t
#include "wire.h" // wire_print, wire_t


void circuit_print(circuit_t *circ) {
  printf("Circuit %s:\n", circ->name);
  printf("%lu gates, %lu wires\n\n", circ->gates.amount, circ->wires.amount);

  // Print gates
  for (size_t i = 0; i < circ->gates.amount; i++) {
    printf("gate %lu: ", i);

    gate_print((gate_t*) circ->gates.items[i]);
    printf("\n");
  }

  printf("\n");

  // Print wires
  for (size_t i = 0; i < circ->wires.amount; i++) {
    printf("wire %lu: ", i);

    wire_print((wire_t*) circ->wires.items[i]);
    printf("\n");
  }
}


void circuit_init(circuit_t *circ) {
  circ->name = NULL;

  vector_init(&circ->gates, BUF_SIZE);
  vector_init(&circ->wires, BUF_SIZE);
}


void circuit_free(circuit_t *circ) {
  if (circ->name) free(circ->name);

  // Free gates
  for (size_t i=0; i < circ->gates.amount; i++) {
    gate_free(circ->gates.items[i]);
    free(circ->gates.items[i]);
  }

  vector_free(&circ->gates);


  // Free wires
  for (size_t i=0; i < circ->wires.amount; i++) {
    wire_free(circ->wires.items[i]);
    free(circ->wires.items[i]);
  }

  vector_free(&circ->wires);
}
