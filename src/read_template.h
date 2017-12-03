#ifndef READ_TEMPLATE_H
#define READ_TEMPLATE_H

#include <stdlib.h>

#include "gate.h"
#include "wire.h"

struct gate_template {
  char gatename[BUF_SIZE];
  size_t amount_gates;
  struct gate gates[BUF_SIZE];
  size_t amount_wires;
  struct wire wires[BUF_SIZE];
};


void read_template(char *filename, struct gate_template *temp);

#endif
