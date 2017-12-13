#include <stdio.h> // printf

#include "port.h"

#include "defines.h"
#include "bool.h" // bool_print


void port_print(port_t *port) {
  printf("%c (", port->name);
  bool_print(port->state);
  printf(")");
}


void port_init(port_t *port) {
  port->name = '?';
  port->state = false;
}


void port_free(port_t *port) {
  (void) port;
}
