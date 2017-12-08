#include <stdio.h>
#include <string.h>

#include "gate.h"


void gate_to_string(struct gate *gate, char *str) {
  sprintf(str, "{ [%s] %s }", gate->type, gate->name);

  for (unsigned int i = 0; i < gate->amount_ports; i++) {
    struct port *p = gate->ports[i];

    char buf[BUF_SIZE];
    port_to_string(p, buf);

    char tmp[BUF_SIZE];
    sprintf(tmp, "%s%s", str, buf);
    memmove(str, tmp, sizeof(tmp));

    printf("%s\n", tmp);
  }
}
