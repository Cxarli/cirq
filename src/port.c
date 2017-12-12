#include <stdio.h>

#include "defines.h"
#include "port.h"
#include "bool.h"


void print_port(port_t *port) {
  printf("%c (", port->name);
  print_bool(port->state);
  printf(")");
}
