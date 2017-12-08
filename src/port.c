#include <stdio.h>

#include "defines.h"
#include "port.h"
#include "bool.h"


void port_to_string(struct port *port, char *str) {
  char tmp[BUF_SIZE];
  bool_to_str(port->state, tmp);

  sprintf(str, "%c (%s)", port->name, tmp);
}
