#include <stdio.h> // printf
#include <string.h> // strcmp

#include "circuit.h"

#include "utils.h"


bool circuit_apply_wire(circuit_t *circ, wire_t *wire) {
  port_t *left_port = NULL;
  port_t *right_port = NULL;

  // Get the matching ports
  VEC_EACH(circ->gates, gate_t *gate) {
    switch_str(gate->name) {
      case_str(wire->leftuuid) {
        left_port = gate_get_port_by_name(gate, wire->leftport);
      }

      // NOTE: Using `else` disables the possibility to link a gate to itself
      case_str(wire->rightuuid) {
        right_port = gate_get_port_by_name(gate, wire->rightport);
      }
    }
  }

  // Make sure we got all ports
  if (left_port == NULL || right_port == NULL) {
    STDOUT_TO_STDERR();

    printf("Failed to find both ports for wire ");
    wire_print(wire);
    printf("\n");

    RESET_STDOUT();
    return false;
  }

  // Add connection
  vector_push(&left_port->connections, right_port);
  vector_push(&right_port->connections, left_port);

  return true;
}


void circuit_update_state(circuit_t *circ) {
  VEC_EACH(circ->gates, gate_t *gate) {
    gate_update_state(gate);
  }
}


gate_t *circuit_get_gate_by_name(circuit_t *circ, char *name) {
  VEC_EACH(circ->gates, gate_t *gate) {
    if (strcmp(gate->name, name) == 0) {
      return gate;
    }
  }

  fprintf(stderr, "Failed to find gate '%s'\n", name);
  return NULL;
}


port_t *circuit_get_port_by_name(circuit_t *circ, char *gatename, char *portname) {
  return gate_get_port_by_name(circuit_get_gate_by_name(circ, gatename), portname);
}


void circuit_print(circuit_t *circ) {
  printf("Circuit %s: %lu gates\n\n", circ->name, circ->gates.amount);

  // Print gates
  for (size_t i = 0; i < circ->gates.amount; i++) {
    printf("gate %lu: ", i);

    gate_print(circ->gates.items[i]);
    printf("\n");
  }
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
    free(g);
  }

  vector_free(&circ->gates);
}
