#include <stdio.h>

#include "read_template.h"
#include "circuit.h"
#include "vector.h"
#include "gate.h"
#include "wire.h"
#include "test.h"


unsigned int test_full_adder(void) {
  TEST_START;

  // Create circuit
  circuit_t *circ = malloc(sizeof(circuit_t));
  circuit_init(circ);

  // Read template
  assert_true(read_template("tests/full_adder", circ));

  // Free everything
  circuit_free(circ);
  free(circ);

  TEST_END;
}
