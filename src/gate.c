#include "gate.h"

#include "circuit.h"
#include "assert.h"
#include "benchmark.h"


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
			// Check if we have dependencies
			if (dependencies == NULL) {
				goto no_deps;
			}

			// Try to find circuit in dependencies
			circuit_t *custom = NULL;

			for (size_t i = 0; i < dependencies->amount; i++) {
				circuit_t *dep = dependencies->items[i];

				if (strcmp(dep->name, gate->type) == 0) {
					custom = dep;
					break;
				}
			}

			// If failed to find custom circuit
			if (custom == NULL) {
				no_deps:
				warn("Failed to set ports for gate of type %s", gate->type);
				return false;
			}

			// Copy circuit to inner circuit
			gate->inner_circuit = malloc(sizeof(circuit_t));
			memcpy(gate->inner_circuit, custom, sizeof(circuit_t));

			// Take gates from circuit
			FUNC_PAUSE();
			success &= gate_take_gates_from_circuit(gate, custom);
			FUNC_RESUME();

			FUNC_END();
			return success;
		}
	}


	// We shouldn't reach this
	FUNC_END();
	return false;
}


bool gate_take_gates_from_circuit(gate_t *gate, circuit_t *circuit) {
	FUNC_START();

	assert_not_null(gate);
	assert_not_null(circuit);


	bool success = true;


	VEC_EACH(circuit->gates, gate_t *g) {
		assert_not_null(g);

		char *newportname = NULL;

		if (! gate_is_io(g)) {
			continue;
		}

		// Get old portname
		char *portname = ((port_t *) g->ports.items[0])->name;
		assert_not_null(portname);

		// Copy portname
		newportname = malloc(sizeof(portname) * sizeof(char));
		strcpy(newportname, portname);

		// Add new gate
		switch_str(g->type) {
			case_str("IN") {
				FUNC_PAUSE();
				success &= gate_add_input(gate, 0, newportname);
				FUNC_RESUME();
			}

			// There is only one other option: OUT
			else {
				FUNC_PAUSE();
				success &= gate_add_output(gate, 0, newportname);
				FUNC_RESUME();
			}
		}
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
			o0->state = i0->state && i1->state;

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
			o0->state = i0->state || i1->state;

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

			// Mirror outer gate state to inner circuit
			VEC_EACH(gate->ports, port_t *port) {
				FUNC_PAUSE();
				port_t *inner_port = circuit_get_io_port_by_name(gate->inner_circuit, port->name);
				success &= port_set_state(inner_port, port->state);
				FUNC_RESUME();
			}

			// Update inner circuit
			FUNC_PAUSE();
			success &= circuit_update_state(gate->inner_circuit);
			FUNC_RESUME();

			// Mirror inner circuit state to outer gate
			VEC_EACH(gate->inner_circuit->gates, gate_t *inner_gate) {
				// Filter on output only
				if (strcmp(inner_gate->type, "OUT") != 0) {
					continue;
				}

				port_t *inner_port = inner_gate->ports.items[0];

				FUNC_PAUSE();
				port_t *outer_port = gate_get_port_by_name(gate, inner_port->name);

				success &= port_set_state(outer_port, inner_port->state);
				FUNC_RESUME();
			}


			FUNC_END();
			return success;
		}
	}


	// Shouldn't reach this
	FUNC_END();
	return false;
}


bool gate_is_io(gate_t *gate) {
	FUNC_START();

	bool is_io = strcmp(gate->type, "IN") == 0 || strcmp(gate->type, "OUT") == 0;
	FUNC_END();
	return is_io;
}


void gate_print(gate_t *gate) {
	printf("{ %s [%s] }\n", gate->name, gate->type);

	VEC_EACH(gate->ports, port_t* p) {
		printf("\t");
		port_print(p);
		printf("\n");
	}


	if (gate->inner_circuit != NULL) {
		printf("INNER:\n");
		circuit_print(gate->inner_circuit);
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

	// NOTE: Don't circuit_free this
	if (gate->inner_circuit) free(gate->inner_circuit);

	// Free all ports
	VEC_EACH(gate->ports, port_t* p) {
		port_free(p);
		free(p);
	}

	vector_free(&gate->ports);
}
