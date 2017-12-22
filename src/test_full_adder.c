#include "read_template.h"
#include "test.h"


#define DEBUG_PRINT_GATE(name) \
	printf("\t"); gate_print(circuit_get_gate_by_name(&fa_circ, name), 0); printf("\n"); \

#define DEBUG_PRINT() \
	DEBUG_PRINT_GATE("0e36e9ea"); \
	DEBUG_PRINT_GATE("63f0d9e3"); \
	DEBUG_PRINT_GATE("b9f8820d"); \
	\
	DEBUG_PRINT_GATE("2c9ced3a"); \
	DEBUG_PRINT_GATE("57f26486"); \
	\
	DEBUG_PRINT_GATE("3752723b"); \
	DEBUG_PRINT_GATE("45243a79"); \
	\
	DEBUG_PRINT_GATE("e16e5e97"); \


test_result_t test_full_adder(void) {
	TEST_START;

	// Create circuit
	circuit_t ha_circ;
	circuit_init(&ha_circ);
	circuit_t fa_circ;
	circuit_init(&fa_circ);

	vector_t deps;
	vector_init(&deps, 4);

	// Read templates
	assert_true(read_template("tests/half_adder", &ha_circ, NULL));
	assert_true(vector_push(&deps, &ha_circ));

	assert_true(read_template("tests/full_adder", &fa_circ, &deps));


	// ... Do fun things

	// Get all I/O gates

	/*
	0e36e9ea IN #I0
	63f0d9e3 IN #I1
	b9f8820d IN #Ci
	2c9ced3a OUT #S
	57f26486 OUT #Co
	*/

	port_t *i0 = circuit_get_port_by_name(&fa_circ, "0e36e9ea", "I0");
	port_t *i1 = circuit_get_port_by_name(&fa_circ, "63f0d9e3", "I1");
	port_t *ici = circuit_get_port_by_name(&fa_circ, "b9f8820d", "Ci");
	port_t *os = circuit_get_port_by_name(&fa_circ, "2c9ced3a", "S");
	port_t *oco = circuit_get_port_by_name(&fa_circ, "57f26486", "Co");

	// Make sure we got them
	assert_not_null(i0);
	assert_not_null(i1);
	assert_not_null(ici);
	assert_not_null(os);
	assert_not_null(oco);

	// Check their types
	assert_eq(i0->type, PortType_OUTPUT);
	assert_eq(i1->type, PortType_OUTPUT);
	assert_eq(ici->type, PortType_OUTPUT);
	assert_eq(os->type, PortType_INPUT);
	assert_eq(oco->type, PortType_INPUT);

	// Make sure default inputs are false
	assert_eq(i0->state, false);
	assert_eq(i1->state, false);
	assert_eq(ici->state, false);

	// A B C -> C S
	// 0 0 0 -> 0 0
	port_set_state(i0, false);
	port_set_state(i1, false);
	port_set_state(ici, false);
	assert_eq(oco->state, false);
	assert_eq(os->state, false);
	printf("0 0 0\n");
	DEBUG_PRINT();

	// A B C -> C S
	// 0 0 1 -> 0 1
	port_set_state(i0, false);
	port_set_state(i1, false);
	port_set_state(ici, true);
	assert_eq(oco->state, false);
	assert_eq(os->state, true);
	printf("0 0 1\n");
	DEBUG_PRINT();

	// A B C -> C S
	// 0 1 0 -> 0 1
	port_set_state(i0, false);
	port_set_state(i1, true);
	port_set_state(ici, false);
	assert_eq(oco->state, false);
	assert_eq(os->state, true);
	printf("0 1 0\n");
	DEBUG_PRINT();

	// A B C -> C S
	// 0 1 1 -> 1 0
	port_set_state(i0, false);
	port_set_state(i1, true);
	port_set_state(ici, true);
	assert_eq(oco->state, true);
	assert_eq(os->state, false);
	printf("0 1 1\n");
	DEBUG_PRINT();

	// A B C -> C S
	// 1 0 0 -> 0 1
	port_set_state(i0, true);
	port_set_state(i1, false);
	port_set_state(ici, false);
	assert_eq(oco->state, false);
	assert_eq(os->state, true);
	printf("1 0 0\n");
	DEBUG_PRINT();

	// A B C -> C S
	// 1 0 1 -> 1 0
	port_set_state(i0, true);
	port_set_state(i1, false);
	port_set_state(ici, true);
	assert_eq(oco->state, true);
	assert_eq(os->state, false);
	printf("1 0 1\n");
	DEBUG_PRINT();

	// A B C -> C S
	// 1 1 0 -> 1 0
	port_set_state(i0, true);
	port_set_state(i1, true);
	port_set_state(ici, false);
	assert_eq(oco->state, true);
	assert_eq(os->state, false);
	printf("1 1 0\n");
	DEBUG_PRINT();

	// A B C -> C S
	// 1 1 1 -> 1 1
	port_set_state(i0, true);
	port_set_state(i1, true);
	port_set_state(ici, true);
	assert_eq(oco->state, true);
	assert_eq(os->state, true);
	printf("1 1 1\n");
	DEBUG_PRINT();


	// Free everything
	circuit_free(&fa_circ);
	circuit_free(&ha_circ);
	vector_free(&deps);

	TEST_END;
}
