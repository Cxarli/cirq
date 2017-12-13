#include <stdio.h>

#include "read_template.h"
#include "circuit.h"
#include "vector.h"
#include "gate.h"
#include "wire.h"


int main() {
  circuit_t circ;
  circuit_init(&circ);

  DEBUG;

  read_template("tests/template", &circ);
  printf("\n\n");

  DEBUG;

  circuit_print(&circ);

  DEBUG;

  circuit_free(&circ);
}
