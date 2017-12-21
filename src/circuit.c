#include "circuit.h"

#include "utils.h"
#include "assert.h"
#include "benchmark.h"


bool circuit_apply_wire(circuit_t *circ, wire_t *wire) {
	FUNC_START();

	assert_not_null(circ);
	assert_not_null(wire);

	// Get the matching gates
	gate_t *left_gate = circuit_get_gate_by_name(circ, wire->leftuuid);
	gate_t *right_gate = circuit_get_gate_by_name(circ, wire->rightuuid);

	if (left_gate == NULL || right_gate == NULL) {
		goto fail;
	}

	port_t *left_port = gate_get_port_by_name(left_gate, wire->leftport);
	port_t *right_port = gate_get_port_by_name(right_gate, wire->rightport);

	// Make sure we got all ports
	if (left_port == NULL || right_port == NULL) {
		fail:
		STDOUT_TO_STDERR();

		printf("Failed to find both ports for wire ");
		wire_print(wire);
		printf("\n");

		RESET_STDOUT();
		FUNC_END();
		return false;
	}


	// Add connection
	assert(vector_push(&left_port->connections, right_port));
	assert(vector_push(&right_port->connections, left_port));


	FUNC_END();
	return true;
}


bool circuit_update_state(circuit_t *circ) {
	FUNC_START();

	assert_not_null(circ);

	bool success = true;

	HEX_HASHMAP_EACH_VALUE(circ->gates, gate_t *gate) {
		assert_not_null(gate);

		FUNC_PAUSE();
		success &= gate_update_state(gate);
		FUNC_RESUME();
	}

	FUNC_END();
	return success;
}


gate_t *circuit_get_gate_by_name(circuit_t *circ, char *name) {
	FUNC_START();

	assert_not_null(circ);
	assert_not_null(name);


	gate_t *gate = hex_hashmap_get_item(&circ->gates, name);

	if (gate == NULL) {
		warn("Failed to find gate %s in circuit %s", name, circ->name);
		FUNC_END();
		return NULL;
	}

	FUNC_END();
	return gate;
}


port_t *circuit_get_port_by_name(circuit_t *circ, char *gatename, char *portname) {
	FUNC_START();

	assert_not_null(circ);
	assert_not_null(gatename);
	assert_not_null(portname);

	FUNC_PAUSE();
	gate_t *gate = circuit_get_gate_by_name(circ, gatename);
	assert_not_null(gate);
	FUNC_RESUME();

	FUNC_PAUSE();
	port_t *port = gate_get_port_by_name(gate, portname);
	FUNC_RESUME();

	FUNC_END();
	return port;
}


port_t *circuit_get_io_port_by_name(circuit_t *circ, char *portname) {
	FUNC_START();

	assert_not_null(circ);
	assert_not_null(portname);


	HEX_HASHMAP_EACH_VALUE(circ->gates, gate_t *gate) {
		assert_not_null(gate);

		// Filter on I/O ports only
		if (! gate_is_io(gate)) {
			continue;
		}

		// Check portname
		port_t *port = gate->ports.items[0];

		if (strcmp(port->name, portname) == 0) {
			FUNC_END();
			return port;
		}
	}

	warn("Failed to find I/O port %s for circuit %s", portname, circ->name);
	FUNC_END();
	return NULL;
}


void circuit_print(circuit_t *circ) {
	assert_not_null(circ);

	printf("Circuit %s: %lu gates\n\n", circ->name, hex_hashmap_amount(&circ->gates));

	HEX_HASHMAP_EACH_VALUE_INDEX(circ->gates, gate_t *gate, i) {
		printf("gate %lu: ", i);

		gate_print(gate);
		printf("\n");
	}
}


void circuit_init(circuit_t *circ) {
	assert_not_null(circ);

	circ->name = NULL;

	hex_hashmap_init(&circ->gates);
}


void circuit_free(circuit_t *circ) {
	assert_not_null(circ);

	if (circ->name) free(circ->name);

	// Free gates
	HEX_HASHMAP_EACH_VALUE(circ->gates, gate_t* g) {
		assert_not_null(g);

		gate_free(g);
		free(g);
	}

	hex_hashmap_free(&circ->gates);
}
