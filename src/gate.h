#ifndef GATE_H
#define GATE_H

#include "defines.h"


struct gate {
  char name[BUF_SIZE];
  char type[BUF_SIZE];
};

void gate_to_string(struct gate *gate, char *str);

#endif
