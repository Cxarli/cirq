#ifndef PORT_H
#define PORT_H

#include "bool.h"


typedef struct port {
  char name;
  bool state;
} port_t;


void print_port(port_t *port);

#endif
