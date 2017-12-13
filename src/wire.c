#include <stdio.h>

#include "wire.h"


void wire_print(wire_t *wire) {
  printf("%s:%s <---> %s:%s", wire->leftuuid, wire->leftport, wire->rightuuid, wire->rightport);
}
