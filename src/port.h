#ifndef PORT_H
#define PORT_H


#include <stdbool.h>

#include "defines.h"
#include "vector.h"

// forward-declaration
typedef struct gate gate_t;


enum PortType {
  PortType_INPUT,
  PortType_OUTPUT
};



typedef struct port {
  char *name;
  bool state;
  enum PortType type;

  gate_t *gate;
  vector_t connections;
} port_t;


void port_update_state(port_t *port);
void port_set_state(port_t *port, bool state);
bool port_get_state(port_t *port);

void port_print(port_t *port);
void port_init(port_t *port);
void port_free(port_t *port);

#endif
