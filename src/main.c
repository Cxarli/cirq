#include <stdio.h>

#include "defines.h"
#include "read_template.h"
#include "gate.h"
#include "wire.h"


int main() {
  char *filename = "tests/template";

  struct gate_template gate;

  read_template(filename, &gate);
  printf("\n\n");


  printf("Gate %s:\n", gate.gatename);
  printf("%lu gates, %lu wires\n", gate.amount_gates, gate.amount_wires);

  char str[BUF_SIZE];

  printf("\n");
  for (unsigned int i = 0; i < gate.amount_gates; i++) {
    gate_to_string(&gate.gates[i], str);
    printf("gate %u: %s\n", i, str);
  }

  printf("\n");
  for (unsigned int i = 0; i < gate.amount_wires; i++) {
    wire_to_string(&gate.wires[i], str);
    printf("wire %u: %s\n", i, str);
  }
}
