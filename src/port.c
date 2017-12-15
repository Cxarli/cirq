#include <stdio.h> // printf

#include "port.h"

#include "bool.h" // bool_print
#include "gate.h" // gate_t


void port_update_state(port_t *port) {
  if (port->type == PortType_INPUT) {
    gate_update_state(port->gate);
  }
  else {
    // If port is an output, copy state to other inputs
    VEC_EACH(port->connections, port_t *connection) {
      if (connection->type == PortType_INPUT) {
        connection->state = port->state;
        port_update_state(connection);
      }
    }
  }
}


void port_set_state(port_t *port, bool state) {
  port->state = state;
  port_update_state(port);
}


bool port_get_state(port_t *port) {
  return port->state;
}


void port_print(port_t *port) {
  printf("    :%s (", port->name);
  bool_print(port->state);
  printf(") --> ");

  // Print the connections
  VEC_EACH(port->connections, port_t *connection) {
    char *gatename = connection->gate->name;
    printf("%s:%s%s", gatename, connection->name, __last ? "" : ", ");
  }
}


void port_init(port_t *port) {
  port->name = NULL;
  port->gate = NULL;

  // Defaults
  port->state = false;
  port->type = PortType_OUTPUT;

  vector_init(&port->connections, BUF_SIZE);
}


void port_free(port_t *port) {
  if (port->name) free(port->name);

  vector_free(&port->connections);
}
