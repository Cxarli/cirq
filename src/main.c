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

  // Set state of first input to true
  port_t *i0 = gate_get_port_by_name(circuit_get_gate_by_name(circ, "da2ecd25"), "O0");
  port_t *i1 = gate_get_port_by_name(circuit_get_gate_by_name(circ, "daa53637"), "O0");

  port_set_state(i0, true);
  port_set_state(i1, true);

  circuit_print(circ);

  circuit_free(circ);
  free(circ);
}
