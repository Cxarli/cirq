#include <stdio.h>

#include "defines.h"
#include "port.h"
#include "bool.h"


void port_print(port_t *port) {
  printf("%c (", port->name);
  bool_print(port->state);
  printf(")");
}
