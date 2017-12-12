#include <stdio.h>

#include "wire.h"


void print_wire(wire_t *wire) {
  printf("%s:%s <---> %s:%s", wire->leftuuid, wire->leftport, wire->rightuuid, wire->rightport);
}
