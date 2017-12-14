#include <stdio.h> // printf

#include "port.h"

#include "bool.h" // bool_print


void port_print(port_t *port) {
  printf("    :%s (", port->name);
  bool_print(port->state);
  printf(") --> ");

  // Print the connections
  VEC_EACH(port->connections, port_t *connection) {
    printf("%s:%s%s", connection->gatename, connection->name, __last ? "" : ", ");
  }
}


void port_init(port_t *port) {
  port->name = NULL;
  port->gatename = NULL;

  // Defaults
  port->state = false;
  port->type = PortType_OUTPUT;

  vector_init(&port->connections, BUF_SIZE);
}


void port_free(port_t *port) {
  if (port->name) free(port->name);

  vector_free(&port->connections);

  free(port);
}
