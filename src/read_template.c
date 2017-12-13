#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defines.h"
#include "read_template.h"
#include "gate.h"
#include "wire.h"
#include "circuit.h"
#include "port.h"
#include "vector.h"


void read_template(char *filename, circuit_t *circ) {
  char buf[BUF_SIZE];

  // Open file
  FILE *file = fopen(filename, "r");

  // Get name, which is always the first thing in a file
  // example: NAND
  fscanf(file, "%s\n", circ->name);
  printf("name: %s\n", circ->name);

  // Get gates, which are always second
  // example:  [gates] 16
  size_t amount_gates;

  fscanf(file, "%s %lu\n", buf, &amount_gates);

  if ( strcmp(buf, "[gates]") != 0 ) {
    printf("no [gates]?? '%s' unexpected\n", buf);
    return;
  }

  printf("[gates] %lu\n", amount_gates);

  DEBUG;

  for (size_t i = 0; i < amount_gates; i++) {
    char *name = malloc(BUF_SIZE);
    char *type = malloc(BUF_SIZE);

    DEBUG;

    // example:  6306ee7f NOT
    int x = fscanf(file, "%s %s\n", name, type);

    if ( x == -1 ) {
      // Unexpected end of file
      printf("EOF??\n");
      break;
    }

    DEBUG;

    gate_t g;
    g.name = name;
    g.type = type;

    DEBUG;

    gate_print(&g);
    printf("\n");

    DEBUG;

    vector_push(&circ->gates, &g);

    DEBUG;
  }


  // Get wires, which are third
  // example:  [wires] 20
  size_t amount_wires;

  fscanf(file, "%s %lu\n", buf, &amount_wires);

  if ( strcmp(buf, "[wires]") != 0 ) {
    printf("no [wires]?? '%s' unexpected\n", buf);
    return;
  }

  printf("[wires] %lu\n", amount_wires);


  DEBUG;

  for (size_t i = 0; i < amount_wires; i++) {
    char *leftuuid = malloc(BUF_SIZE);
    char *leftport = malloc(BUF_SIZE);
    char *rightuuid = malloc(BUF_SIZE);
    char *rightport = malloc(BUF_SIZE);

    DEBUG;

    // example:  da2ecd25:O0 eec2fc01:I0
    int x = fscanf(file, "%[a-f0-9]:%s %[a-f0-9]:%s\n", leftuuid, leftport, rightuuid, rightport);

    if ( x == -1 ) {
      // Unexpected end of file
      printf("EOF??\n");
      break;
    }

    DEBUG;

    wire_t w;
    w.leftuuid = leftuuid;
    w.leftport = leftport;
    w.rightuuid = rightuuid;
    w.rightport = rightport;

    DEBUG;

    wire_print(&w);
    printf("\n");

    DEBUG;

    vector_push(&circ->wires, &w);

    DEBUG;
  }

}
