#include <stdio.h> // printf
#include <string.h> // strcmp

#include "gate.h"


void gate_print(gate_t *gate) {
  printf("{ %s [%s] }\n", gate->name, gate->type);

  VEC_EACH(gate->ports, port_t* p) {
    printf("\t");
    port_print(p);
    printf("\n");
  }
}


void gate_init(gate_t *gate) {
  gate->name = NULL;
  gate->type = NULL;

  vector_init(&gate->ports, BUF_SIZE);
}


void gate_add_input(gate_t *gate, int i, char name[]) {
  if (name == NULL) {
    // Set default name
    name = malloc(11 * sizeof(char));
    sprintf(name, "I%i", i);
  }

  // Create port
  port_t *p = malloc(sizeof(port_t));
  port_init(p);

  p->name = name;
  p->gatename = gate->name;
  p->type = PortType_INPUT;

  // Add port
  vector_push(&gate->ports, p);
}


void gate_add_output(gate_t *gate, int i, char *name) {
  if (name == NULL) {
    // Set default name
    name = malloc(11 * sizeof(char));
    sprintf(name, "O%i", i);
  }

  // Create port
  port_t *p = malloc(sizeof(port_t));
  port_init(p);

  p->name = name;
  p->gatename = gate->name;
  p->type = PortType_OUTPUT;

  // Add port
  vector_push(&gate->ports, p);
}


void gate_set_ports(gate_t *gate) {
  switch_str(gate->type) {
    case_str("AND") {
      gate_add_input(gate, 0, NULL);
      gate_add_input(gate, 1, NULL);
      gate_add_output(gate, 0, NULL);
    }

    else case_str("OR") {
      gate_add_input(gate, 0, NULL);
      gate_add_input(gate, 1, NULL);
      gate_add_output(gate, 0, NULL);
    }

    else case_str("NOT") {
      gate_add_input(gate, 0, NULL);
      gate_add_output(gate, 0, NULL);
    }

    else case_str("IN") {
      gate_add_output(gate, 0, NULL);
    }

    else case_str("OUT") {
      gate_add_input(gate, 0, NULL);
    }

    // TODO: Custom gates
  }
}


void gate_free(gate_t *gate) {
  if (gate->name) free(gate->name);
  if (gate->type) free(gate->type);

  // Free all ports
  VEC_EACH(gate->ports, port_t* p) {
    port_free(p);
    free(p);
  }

  vector_free(&gate->ports);
}
