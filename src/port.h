#ifndef PORT_H
#define PORT_H

#include "bool.h"


struct port {
  char name;
  bool state;
};

void port_to_string(struct port *port, char *str);

#endif
