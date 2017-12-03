#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defines.h"
#include "read_template.h"
#include "gate.h"
#include "wire.h"
#include "circuit.h"


void read_template(char *filename, struct circuit *circ) {
  char buf[BUF_SIZE];

  // Open file
  FILE *file = fopen(filename, "r");

  // Get name, which is always the first thing in a file
  // example: NAND
  fscanf(file, "%s\n", circ->name);
  printf("name: %s\n", circ->name);

  // Get gates, which are always second
  // example:  [gates] 16
  fscanf(file, "%s %lu\n", buf, &circ->amount_gates);
  if ( strcmp(buf, "[gates]") != 0 ) {
    printf("no [gates]?? '%s' unexpected\n", buf);
    return;
  }
  printf("[gates] %lu\n", circ->amount_gates);


  for (unsigned int i = 0; i < circ->amount_gates; i++) {
    char name[BUF_SIZE];
    char type[BUF_SIZE];

    // example:  6306ee7f NOT
    int x = fscanf(file, "%s %s\n", name, type);

    if ( x == -1 ) {
      // Unexpected end of file
      printf("EOF??\n");
      break;
    }

    struct gate g;

    memmove(g.name, name, BUF_SIZE);
    memmove(g.type, type, BUF_SIZE);

    circ->gates[i] = g;

    printf("[%u] gatename: %s, type: %s\n", i, circ->gates[i].name, circ->gates[i].type);
  }


  // Get wires, which are third
  // example:  [wires] 20
  fscanf(file, "%s %lu\n", buf, &circ->amount_wires);
  if ( strcmp(buf, "[wires]") != 0 ) {
    printf("no [wires]?? '%s' unexpected\n", buf);
    return;
  }
  printf("[wires] %lu\n", circ->amount_wires);


  for (unsigned int i = 0; i < circ->amount_wires; i++) {
    char leftuuid[BUF_SIZE];
    char leftport[BUF_SIZE];
    char rightuuid[BUF_SIZE];
    char rightport[BUF_SIZE];

    // example:  da2ecd25:O0 eec2fc01:I0
    int x = fscanf(file, "%[a-f0-9]:%s %[a-f0-9]:%s\n", leftuuid, leftport, rightuuid, rightport);

    if ( x == -1 ) {
      // Unexpected end of file
      printf("EOF??\n");
      break;
    }

    struct wire w;
    memmove(w.leftuuid, leftuuid, BUF_SIZE);
    memmove(w.leftport, leftport, BUF_SIZE);
    memmove(w.rightuuid, rightuuid, BUF_SIZE);
    memmove(w.rightport, rightport, BUF_SIZE);
    circ->wires[i] = w;

    printf("leftuuid: %s, leftport: %s, rightuuid: %s, rightport: %s\n", w.leftuuid, w.leftport, w.rightuuid, w.rightport);
  }

}
