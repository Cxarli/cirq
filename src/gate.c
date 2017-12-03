#include <stdio.h>

#include "gate.h"

void gate_to_string(struct gate *gate, char *str) {
  sprintf(str, "{ [%s] %s }", gate->type, gate->name);
}
