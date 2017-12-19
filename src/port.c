#include "port.h"

#include "bool.h"
#include "gate.h"
#include "assert.h"


bool port_update_state(port_t *port) {
	assert_not_null(port);

	bool success = true;

	if (port->type == PortType_INPUT) {
		// Input ports should update the gate they are attached to
		success &= gate_update_state(port->gate);
	}

	else if (port->type == PortType_OUTPUT) {
		// Output ports should copy their state to their connected input ports
		VEC_EACH(port->connections, port_t *connection) {
			success &= port_set_state(connection, port->state);
		}
	}

	else {
		panic("Port %s:%s has invalid type", port->gate->name, port->name);
	}

	return success;
}


bool port_set_state(port_t *port, bool state) {
	port->state = state;
	return port_update_state(port);
}


void port_print(port_t *port) {
	printf("    :%s (", port->name);
	bool_print(port->state);
	printf(")");

	// Print an arrow when it has a connection only
	if (port->connections.amount > 0) {
		printf(" --> ");
	}

	// Print the connections
	VEC_EACH_INDEX(port->connections, port_t *connection, i) {
		char *gatename = connection->gate->name;

		printf("%s:%s", gatename, connection->name);

		// Print a comma when it's not the last item
		if (i < port->connections.amount - 1) {
			printf(", ");
		}
	}
}


void port_init(port_t *port) {
	port->name = NULL;
	port->gate = NULL;

	// Defaults
	port->state = false;
	port->type = PortType_OUTPUT;

	vector_init(&port->connections, BUF_SIZE);
}


void port_free(port_t *port) {
	if (port->name) free(port->name);

	vector_free(&port->connections);
}
