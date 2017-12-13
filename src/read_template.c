#include <stdio.h>
#include <string.h> // strcmp

#include "read_template.h"

#include "defines.h"
#include "gate.h" // gate_print, gate_t
#include "wire.h" // wire_print, wire_t


void read_template(char *filename, circuit_t *circ) {
  char buf[BUF_SIZE];

  // Open file
  FILE *file = fopen(filename, "r");

  // Get name, which is always the first thing in a file
  // example: NAND
  circ->name = malloc(BUF_SIZE * sizeof(char));
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
    char *name = malloc(BUF_SIZE * sizeof(char));
    char *type = malloc(BUF_SIZE * sizeof(char));

    // example:  6306ee7f NOT
    int x = fscanf(file, "%s %s\n", name, type);

    if ( x == -1 ) {
      // Unexpected end of file
      printf("EOF??\n");
      break;
    }

    // New gate
    gate_t *g = malloc(sizeof(gate_t));
    gate_init(g);


    g->name = name;
    g->type = type;


    gate_print(g);
    printf("\n");

    vector_push(&circ->gates, g);
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
    char *leftuuid = malloc(BUF_SIZE * sizeof(char));
    char *leftport = malloc(BUF_SIZE * sizeof(char));
    char *rightuuid = malloc(BUF_SIZE * sizeof(char));
    char *rightport = malloc(BUF_SIZE * sizeof(char));

    // example:  da2ecd25:O0 eec2fc01:I0
    int x = fscanf(file, "%[a-f0-9]:%s %[a-f0-9]:%s\n", leftuuid, leftport, rightuuid, rightport);

    if ( x == -1 ) {
      // Unexpected end of file
      printf("EOF??\n");
      break;
    }

    // New wire
    wire_t *w = malloc(sizeof(wire_t));
    wire_init(w);

    w->leftuuid = leftuuid;
    w->leftport = leftport;
    w->rightuuid = rightuuid;
    w->rightport = rightport;

    wire_print(w);
    printf("\n");

    vector_push(&circ->wires, w);
  }


  fclose(file);

}
