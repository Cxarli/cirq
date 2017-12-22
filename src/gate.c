#include "gate.h"

#include "circuit.h"
#include "assert.h"
#include "benchmark.h"
#include "utils.h"


port_t *gate_get_port_by_name(gate_t *gate, char *name) {
	FUNC_START();

	assert_not_null(gate);
	assert_not_null(name);


	VEC_EACH(gate->ports, port_t *port) {
		assert_not_null(port);

		if (strcmp(port->name, name) == 0) {
			FUNC_END();
			return port;
		}
	}


	warn("Failed to find port %s for gate %s", name, gate->name);
	FUNC_END();
	return NULL;
}


bool gate_add_port(gate_t *gate, unsigned int i, char *name, PortType_t type) {
	FUNC_START();

	assert_not_null(gate);


	if (name == NULL) {
		// Set default name format
		name = malloc(BUF_SIZE * sizeof(char));

		char typechar = (type == PortType_INPUT) ? 'I' : 'O';
		sprintf(name, "%c%i", typechar, i);
	}


	// Create port
	port_t *p = malloc(sizeof(port_t));
	port_init(p);

	p->name = name;
	p->gate = gate;
	p->type = type;

	// Add port
	assert(vector_push(&gate->ports, p));

	FUNC_END();
	return true;
}


bool gate_add_input(gate_t *gate, unsigned int i, char *name) {
	FUNC_START();

	FUNC_PAUSE();
	bool success = gate_add_port(gate, i, name, PortType_INPUT);
	FUNC_RESUME();


	FUNC_END();
	return success;
}


bool gate_add_output(gate_t *gate, unsigned int i, char *name) {
	FUNC_START();

	FUNC_PAUSE();
	bool success = gate_add_port(gate, i, name, PortType_OUTPUT);
	FUNC_RESUME();


	FUNC_END();
	return success;
}


bool gate_add_node(gate_t *gate, char *name) {
	FUNC_START();

	FUNC_PAUSE();
	bool success = gate_add_port(gate, 0, name, PortType_NODE);
	FUNC_RESUME();


	FUNC_END();
	return success;
}


bool gate_set_ports(gate_t *gate, char *portname, vector_t *dependencies) {
	FUNC_START();

	assert_not_null(gate);

	bool success = true;

	switch_str(gate->type) {
		case_str("AND") {
			FUNC_PAUSE();
			success &= gate_add_input(gate, 0, NULL);
			success &= gate_add_input(gate, 1, NULL);
			success &= gate_add_output(gate, 0, NULL);
			FUNC_RESUME();

			return success;
		}


		else case_str("OR") {
			FUNC_PAUSE();
			success &= gate_add_input(gate, 0, NULL);
			success &= gate_add_input(gate, 1, NULL);
			success &= gate_add_output(gate, 0, NULL);
			FUNC_RESUME();

			return success;
		}


		else case_str("XOR") {
			FUNC_PAUSE();
			success &= gate_add_input(gate, 0, NULL);
			success &= gate_add_input(gate, 1, NULL);
			success &= gate_add_output(gate, 0, NULL);
			FUNC_RESUME();

			return success;
		}


		else case_str("NOT") {
			FUNC_PAUSE();
			success &= gate_add_input(gate, 0, NULL);
			success &= gate_add_output(gate, 0, NULL);
			FUNC_RESUME();

			return success;
		}


		else case_str("IN") {
			FUNC_PAUSE();
			success &= gate_add_output(gate, 0, portname);
			FUNC_RESUME();

			return success;
		}


		else case_str("OUT") {
			FUNC_PAUSE();
			success &= gate_add_input(gate, 0, portname);
			FUNC_RESUME();

			return success;
		}


		else {
			// Try to find circuit in dependencies
			circuit_t *custom = find_dependency(dependencies, gate->type);

			// If failed to find custom circuit
			if (custom == NULL) {
				warn("Failed to set ports for gate of type %s", gate->type);
				return false;
			}

			// Copy circuit to inner circuit
			gate->inner_circuit = circuit_copy(custom);

			// Link to inner circuit
			FUNC_PAUSE();
			success &= gate_link_inner_circuit(gate);
			FUNC_RESUME();

			FUNC_END();
			return success;
		}
	}


	warn("Reached invalid clause?");
	FUNC_END();
	return false;
}


bool gate_link_inner_circuit(gate_t *gate) {
	FUNC_START();

	assert_not_null(gate);
	assert_not_null(gate->inner_circuit);


	bool success = true;


	HEX_HASHMAP_EACH_VALUE(gate->inner_circuit->gates, gate_t *inner_gate) {
		assert_not_null(inner_gate);

		if (! gate_is_io(inner_gate)) {
			continue;
		}

		// Get inner port
		port_t *inner_port = inner_gate->ports.items[0];
		assert_not_null(inner_port);

		// Get old portname
		char *portname = inner_port->name;
		assert_not_null(portname);

		// Copy portname
		char *newportname = malloc(sizeof(portname) * sizeof(char));
		strcpy(newportname, portname);

		// Add new port
		success &= gate_add_node(gate, newportname);

		// Copy connections
		port_t *node = gate->ports.items[gate->ports.amount - 1];
		assert(vector_copy(&node->connections, &inner_port->connections));

		VEC_EACH(inner_port->connections, port_t *conn) {
			// Remove old links to the outer gate
			VEC_EACH(conn->connections, port_t *inner_conn) {
				if (inner_conn == inner_port) {
					assert(vector_remove(&conn->connections, inner_port));
				}
			}

			// ... but redirect them to the node directly
			assert(vector_push(&conn->connections, node));
		}

		// Remove IO gate from inner circuit
		hex_hashmap_remove_item(&gate->inner_circuit->gates, inner_gate->name);
		gate_free(inner_gate);
		free(inner_gate);
	}


	FUNC_END();
	return success;
}


bool gate_update_state(gate_t *gate) {
	FUNC_START();

	switch_str(gate->type) {
		case_str("AND") {
			port_t *i0 = gate->ports.items[0];
			port_t *i1 = gate->ports.items[1];
			port_t *o0 = gate->ports.items[2];

			assert_not_null(i0);
			assert_not_null(i1);
			assert_not_null(o0);

			assert_eq(i0->type, PortType_INPUT);
			assert_eq(i1->type, PortType_INPUT);
			assert_eq(o0->type, PortType_OUTPUT);

			// Apply AND
			o0->state = i0->state & i1->state;

			FUNC_PAUSE();
			bool success = port_update_state(o0);
			FUNC_RESUME();

			FUNC_END();
			return success;
		}


		else case_str("OR") {
			port_t *i0 = gate->ports.items[0];
			port_t *i1 = gate->ports.items[1];
			port_t *o0 = gate->ports.items[2];

			assert_not_null(i0);
			assert_not_null(i1);
			assert_not_null(o0);

			assert_eq(i0->type, PortType_INPUT);
			assert_eq(i1->type, PortType_INPUT);
			assert_eq(o0->type, PortType_OUTPUT);

			// Apply OR
			o0->state = i0->state | i1->state;

			FUNC_PAUSE();
			bool success = port_update_state(o0);
			FUNC_RESUME();

			FUNC_END();
			return success;
		}


		else case_str("XOR") {
			port_t *i0 = gate->ports.items[0];
			port_t *i1 = gate->ports.items[1];
			port_t *o0 = gate->ports.items[2];

			assert_not_null(i0);
			assert_not_null(i1);
			assert_not_null(o0);

			assert_eq(i0->type, PortType_INPUT);
			assert_eq(i1->type, PortType_INPUT);
			assert_eq(o0->type, PortType_OUTPUT);

			// Appl XOR
			o0->state = i0->state ^ i1->state;

			FUNC_PAUSE();
			bool success = port_update_state(o0);
			FUNC_RESUME();

			FUNC_END();
			return success;
		}


		else case_str("NOT") {
			port_t *i0 = gate->ports.items[0];
			port_t *o0 = gate->ports.items[1];

			assert_not_null(i0);
			assert_not_null(o0);

			assert_eq(i0->type, PortType_INPUT);
			assert_eq(o0->type, PortType_OUTPUT);

			// Apply NOT
			o0->state = ! i0->state;

			FUNC_PAUSE();
			bool success = port_update_state(o0);
			FUNC_RESUME();

			FUNC_END();
			return success;
		}


		else case_str("IN") {
			port_t *o0 = gate->ports.items[0];

			assert_not_null(o0);

			assert_eq(o0->type, PortType_OUTPUT);

			FUNC_END();
			return true;
		}


		else case_str("OUT") {
			port_t *i0 = gate->ports.items[0];

			assert_not_null(i0);

			assert_eq(i0->type, PortType_INPUT);

			FUNC_END();
			return true;
		}


		else {
			if (gate->inner_circuit == NULL) {
				warn("Can't update the state of the gate with unknown type %s", gate->type);
				FUNC_END();
				return false;
			}

			bool success = true;

			/*
			// Mirror outer gate state to inner circuit
			VEC_EACH(gate->ports, port_t *port) {
				// Filter on input only
				if (port->type != PortType_INPUT) {
					continue;
				}

				FUNC_PAUSE();

				// Get matching inner port
				port_t *inner_port = circuit_get_io_port_by_name(gate->inner_circuit, port->name);

				// Copy outer state to inner port
				success &= port_set_state(inner_port, port->state);

				FUNC_RESUME();
			}
			*/

			/*
			// Update inner circuit
			FUNC_PAUSE();
			success &= circuit_update_state(gate->inner_circuit);
			FUNC_RESUME();
			*/

			/*
			// Mirror inner circuit state to outer gate
			HEX_HASHMAP_EACH_VALUE(gate->inner_circuit->gates, gate_t *inner_gate) {
				// Filter on output only
				if (strcmp(inner_gate->type, "OUT") != 0) {
					continue;
				}

				port_t *inner_port = inner_gate->ports.items[0];

				FUNC_PAUSE();
				port_t *outer_port = gate_get_port_by_name(gate, inner_port->name);

				outer_port->state = inner_port->state;
				FUNC_RESUME();
			}
			*/


			FUNC_END();
			return success;
		}
	}


	// Shouldn't reach this
	warn("Reached invalid point!");
	FUNC_END();
	return false;
}


bool gate_is_io(gate_t *gate) {
	FUNC_START();

	bool is_io = strcmp(gate->type, "IN") == 0 || strcmp(gate->type, "OUT") == 0;
	FUNC_END();
	return is_io;
}


gate_t *gate_copy(gate_t *src) {
	FUNC_START();
	assert_not_null(src);

	gate_t *dest = malloc(sizeof(gate_t));
	gate_init(dest);

	// Copy name
	dest->name = malloc(sizeof(src->name) + 1);
	strcpy(dest->name, src->name);

	// Copy type
	dest->type = malloc(sizeof(src->type) + 1);
	strcpy(dest->type, src->type);

	// Copy inner circuit if any
	if (src->inner_circuit != NULL) {
		dest->inner_circuit = circuit_copy(src->inner_circuit);
	}

	// Copy ports
	VEC_EACH(src->ports, port_t *port) {
		assert_not_null(port);

		port_t *new_port = port_copy(port);

		new_port->gate = dest;

		vector_push(&dest->ports, new_port);
	}

	FUNC_END();
	return dest;
}


void gate_print(gate_t *gate, unsigned int depth) {
	assert_not_null(gate);

	// Create prefix
	char prefix[16];
	memset(prefix, 0, 16);
	memset(prefix, '\t', depth);

	printf("[ <0x%04x> %s {%s} ]\n", (0xffff & (unsigned int) gate), gate->name, gate->type);

	VEC_EACH(gate->ports, port_t* p) {
		printf("%s\t", prefix);
		port_print(p);
		printf("\n");
	}


	if (gate->inner_circuit != NULL) {
		printf("\n");
		circuit_print(gate->inner_circuit, depth + 1);
	}
}


void gate_init(gate_t *gate) {
	gate->name = NULL;
	gate->type = NULL;
	gate->inner_circuit = NULL;

	vector_init(&gate->ports, BUF_SIZE);
}


void gate_free(gate_t *gate) {
	if (gate->name) free(gate->name);
	if (gate->type) free(gate->type);

	if (gate->inner_circuit != NULL) {
		circuit_free(gate->inner_circuit);
		free(gate->inner_circuit);
	}

	// Free all ports
	VEC_EACH(gate->ports, port_t* p) {
		port_free(p);
		free(p);
	}

	vector_free(&gate->ports);
}
