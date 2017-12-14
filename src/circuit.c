#include <stdio.h> // printf
#include <string.h> // strcmp

#include "circuit.h"


void circuit_print(circuit_t *circ) {
  printf("Circuit %s: %lu gates\n\n", circ->name, circ->gates.amount);

  // Print gates
  for (size_t i = 0; i < circ->gates.amount; i++) {
    printf("gate %lu: ", i);

    gate_print(circ->gates.items[i]);
    printf("\n");
  }
}


port_t *gate_get_port_by_name(gate_t *gate, char *name) {
  VEC_EACH(gate->ports, port_t *port) {
    if (strcmp(port->name, name) == 0) {
      return port;
    }
  }

  return NULL;
}


void circuit_apply_wire(circuit_t *circ, wire_t *wire) {
  port_t *left_port = NULL;
  port_t *right_port = NULL;

  // Get the matching ports
  VEC_EACH(circ->gates, gate_t *gate) {
    switch_str(gate->name);

    case_str(wire->leftuuid) {
      left_port = gate_get_port_by_name(gate, wire->leftport);
    }

    else case_str(wire->rightuuid) {
      right_port = gate_get_port_by_name(gate, wire->rightport);
    }
  }

  // Make sure we got all ports
  if (left_port == NULL || right_port == NULL) {
    printf("Failed to find both ports for wire ");
    wire_print(wire);
    printf("\n");
    return;
  }

  // Add connection
  vector_push(&left_port->connections, right_port);
  vector_push(&right_port->connections, left_port);
}


void circuit_init(circuit_t *circ) {
  circ->name = NULL;

  vector_init(&circ->gates, BUF_SIZE);
}


void circuit_free(circuit_t *circ) {
  if (circ->name) free(circ->name);

  // Free gates
  VEC_EACH(circ->gates, gate_t* g) {
    gate_free(g);
  }

  vector_free(&circ->gates);
  free(circ);
}
