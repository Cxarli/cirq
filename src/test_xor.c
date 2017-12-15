#include <stdio.h>

#include "read_template.h"
#include "circuit.h"
#include "vector.h"
#include "gate.h"
#include "wire.h"
#include "test.h"


unsigned int test_xor(void) {
  TEST_START;

  // Create circuit
  circuit_t *circ = malloc(sizeof(circuit_t));
  circuit_init(circ);

  // Read template
  read_template("tests/xor", circ);

  // Get all I/O gates
  port_t *i0 = circuit_get_port_by_name(circ, "2138e29d", "O0");
  port_t *i1 = circuit_get_port_by_name(circ, "bf0a3903", "O0");
  port_t *o0 = circuit_get_port_by_name(circ, "4529cffe", "I0");

  // Make sure default inputs are false
  assert_eq(port_get_state(i0), false);
  assert_eq(port_get_state(i1), false);

  // 0 0 -> 0
  port_set_state(i0, false);
  port_set_state(i1, false);
  assert_eq(port_get_state(o0), false);

  // 0 1 -> 1
  port_set_state(i0, true);
  port_set_state(i1, false);
  assert_eq(port_get_state(o0), true);

  // 1 0 -> 1
  port_set_state(i0, false);
  port_set_state(i1, true);
  assert_eq(port_get_state(o0), true);

  // 1 1 -> 0
  port_set_state(i0, true);
  port_set_state(i1, true);
  assert_eq(port_get_state(o0), false);

  // Free everything
  circuit_free(circ);
  free(circ);

  TEST_END;
}
