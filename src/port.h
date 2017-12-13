#ifndef PORT_H
#define PORT_H


#include <stdbool.h>


typedef struct port {
  char name;
  bool state;
} port_t;


void port_print(port_t *port);

void port_init(port_t *port);
void port_free(port_t *port);

#endif
