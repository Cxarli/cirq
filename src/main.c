#include <stdio.h>

#include "defines.h"
#include "read_template.h"
#include "gate.h"
#include "wire.h"


int main() {
  char *filename = "tests/template";

  char gatename[BUF_SIZE];
  size_t amount_gates;
  struct gate gates[BUF_SIZE];
  size_t amount_wires;
  struct wire wires[BUF_SIZE];

  read_template(filename, gatename, gates, &amount_gates, wires, &amount_wires);
  printf("\n\n");


  printf("Gate %s:\n", gatename);
  printf("%lu gates, %lu wires\n", amount_gates, amount_wires);

  char str[BUF_SIZE];

  printf("\n");
  for (unsigned int i = 0; i < amount_gates; i++) {
    gate_to_string(&gates[i], str);
    printf("gate %u: %s\n", i, str);
  }

  printf("\n");
  for (unsigned int i = 0; i < amount_wires; i++) {
    wire_to_string(&wires[i], str);
    printf("wire %u: %s\n", i, str);
  }

}
