#include <stdio.h>

#include "wire.h"


void wire_to_string(struct wire *wire, char *str) {
  sprintf(str, "%s:%s <---> %s:%s", wire->leftuuid, wire->leftport, wire->rightuuid, wire->rightport);
}
