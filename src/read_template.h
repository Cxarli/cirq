#ifndef READ_TEMPLATE_H
#define READ_TEMPLATE_H

#include <stdlib.h>
#include "gate.h"
#include "wire.h"

void read_template(char *filename, char *gatename, struct gate *gates, size_t *amount_gates, struct wire *wires, size_t *amount_wires);

#endif
