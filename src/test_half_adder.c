#include "read_template.h"
#include "test.h"


unsigned int test_half_adder(void) {
  TEST_START;

  // Create circuit
  circuit_t xor_circ;
  circuit_init(&xor_circ);

  circuit_t ha_circ;
  circuit_init(&ha_circ);

  vector_t deps;
  vector_init(&deps, BUF_SIZE);

  // Read XOR circuit
  assert_true(read_template("tests/xor", &xor_circ, NULL));

  DEBUG;

  // Add XOR circuit to deps tree
  vector_push(&deps, &xor_circ);

  // Read Half-Adder circuit
  assert_true(read_template("tests/half_adder", &ha_circ, &deps));

  DEBUG;

  // ... Do fun things

  // Free everything
  circuit_free(&xor_circ);
  circuit_free(&ha_circ);
  vector_free(&deps);

  TEST_END;
}
