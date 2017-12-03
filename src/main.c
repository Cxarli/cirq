#include <stdio.h>

#include "read_template.h"
#include "circuit.h"


int main() {
  struct circuit circ;

  read_template("tests/template", &circ);

  printf("\n\n");

  print_circuit(&circ);
}
