#include <stdio.h>

#include "read_template.h"
#include "circuit.h"
#include "vector.h"
#include "gate.h"
#include "wire.h"


int main() {
  circuit_t *circ = malloc(sizeof(circuit_t));
  circuit_init(circ);

  read_template("tests/template", circ);

  circuit_print(circ);

  circuit_free(circ);
}
