#ifndef PORT_H
#define PORT_H


#include <stdbool.h>

#include "defines.h"
#include "vector.h"


enum PortType {
  PortType_INPUT,
  PortType_OUTPUT
};


typedef struct port {
  char *name;
  char *gatename;
  bool state;
  enum PortType type;

  vector_t connections;
} port_t;


void port_print(port_t *port);
void port_init(port_t *port);
void port_free(port_t *port);

#endif
