#include <stdio.h>

#include "read_template.h"
#include "circuit.h"
#include "vector.h"
#include "gate.h"
#include "wire.h"


int main() {
  circuit_t circ;
  circuit_init(&circ);


  DEBUG;

  read_template("tests/template", &circ);
  printf("\n\n");

  DEBUG;

  circuit_print(&circ);

  DEBUG;


  /*
  // Free all gates
  for (size_t i=0; i < circ.gates.amount; i++) {
    gate_t *g = circ.gates.items[i];
    free(g->name);
    free(g->type);
    free(g->ports->items);
    free(g->ports);
    free(g);
  }
  free(circ.gates->items);
  free(circ.gates);

  // Free all wires
  for (size_t i=0; i < circ.wires->amount; i++) {
    wire_t *w = circ.wires->items[i];
    free(w->leftuuid);
    free(w->leftport);
    free(w->rightuuid);
    free(w->rightport);
    free(w);
  }
  free(circ.wires->items);
  free(circ.wires);
  */
}
