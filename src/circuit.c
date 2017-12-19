#include "circuit.h"

#include "utils.h"
#include "assert.h"


bool circuit_apply_wire(circuit_t *circ, wire_t *wire) {
	assert_not_null(circ);
	assert_not_null(wire);

	port_t *left_port = NULL;
	port_t *right_port = NULL;


	// Get the matching ports
	VEC_EACH(circ->gates, gate_t *gate) {
		assert_not_null(gate);

		switch_str(gate->name) {
			case_str(wire->leftuuid) {
				left_port = gate_get_port_by_name(gate, wire->leftport);

				assert_not_null(left_port);
			}

			// NOTE: Using `else` disables the possibility to link a gate to itself,
			// which can be both desired and not desired
			case_str(wire->rightuuid) {
				right_port = gate_get_port_by_name(gate, wire->rightport);

				assert_not_null(right_port);
			}
		}
	}


	// Make sure we got all ports
	if (left_port == NULL || right_port == NULL) {
		STDOUT_TO_STDERR();

		printf("Failed to find both ports for wire ");
		wire_print(wire);
		printf("\n");

		RESET_STDOUT();
		return false;
	}


	// Add connection
	assert(vector_push(&left_port->connections, right_port));
	assert(vector_push(&right_port->connections, left_port));


	return true;
}


bool circuit_update_state(circuit_t *circ) {
	assert_not_null(circ);

	bool success = true;

	VEC_EACH(circ->gates, gate_t *gate) {
		assert_not_null(gate);

		success &= gate_update_state(gate);
	}

	return success;
}


gate_t *circuit_get_gate_by_name(circuit_t *circ, char *name) {
	assert_not_null(circ);
	assert_not_null(name);


	VEC_EACH(circ->gates, gate_t *gate) {
		assert_not_null(gate);

		if (strcmp(gate->name, name) == 0) {
			return gate;
		}
	}


	warn("Failed to find gate %s in circuit %s", name, circ->name);
	return NULL;
}


port_t *circuit_get_port_by_name(circuit_t *circ, char *gatename, char *portname) {
	assert_not_null(circ);
	assert_not_null(gatename);
	assert_not_null(portname);


	gate_t *gate = circuit_get_gate_by_name(circ, gatename);
	assert_not_null(gate);

	return gate_get_port_by_name(gate, portname);
}


port_t *circuit_get_io_port_by_name(circuit_t *circ, char *portname) {
	assert_not_null(circ);
	assert_not_null(portname);


	VEC_EACH(circ->gates, gate_t *gate) {
		assert_not_null(gate);

		// Filter on I/O ports only
		if (! gate_is_io(gate)) {
			continue;
		}

		// Check portname
		port_t *port = gate->ports.items[0];

		if (strcmp(port->name, portname) == 0) {
			return port;
		}
	}

	warn("Failed to find I/O port %s for circuit %s", portname, circ->name);
	return NULL;
}


void circuit_print(circuit_t *circ) {
	assert_not_null(circ);

	printf("Circuit %s: %lu gates\n\n", circ->name, circ->gates.amount);

	// Print gates
	for (size_t i = 0; i < circ->gates.amount; i++) {
		printf("gate %lu: ", i);

		gate_print(circ->gates.items[i]);
		printf("\n");
	}
}


void circuit_init(circuit_t *circ) {
	assert_not_null(circ);

	circ->name = NULL;

	vector_init(&circ->gates, BUF_SIZE);
}


void circuit_free(circuit_t *circ) {
	assert_not_null(circ);

	if (circ->name) free(circ->name);

	// Free gates
	VEC_EACH(circ->gates, gate_t* g) {
		assert_not_null(g);

		gate_free(g);
		free(g);
	}

	vector_free(&circ->gates);
}
