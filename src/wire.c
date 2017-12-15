#include <stdio.h> // printf
#include <stdlib.h> // free

#include "wire.h"

#include "defines.h"


void wire_print(wire_t *wire) {
  printf("%s:%s <---> %s:%s", wire->leftuuid, wire->leftport, wire->rightuuid, wire->rightport);
}


void wire_print_err(wire_t *wire) {
  fprintf(stderr, "%s:%s <---> %s:%s", wire->leftuuid, wire->leftport, wire->rightuuid, wire->rightport);
}


void wire_init(wire_t *wire) {
  wire->leftuuid = NULL;
  wire->leftport = NULL;
  wire->rightuuid = NULL;
  wire->rightport = NULL;
}


void wire_free(wire_t *wire) {
  if (wire->leftuuid) free(wire->leftuuid);
  if (wire->leftport) free(wire->leftport);
  if (wire->rightuuid) free(wire->rightuuid);
  if (wire->rightport) free(wire->rightport);
}
