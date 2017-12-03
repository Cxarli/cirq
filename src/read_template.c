#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defines.h"
#include "read_template.h"
#include "gate.h"
#include "wire.h"


void read_template(char *filename, struct gate_template *temp) {
  FILE *file = fopen(filename, "r");

  // First is always the name
  fscanf(file, "%s\n", temp->gatename);
  printf("name: %s\n", temp->gatename);

  // Second should be [gates]
  char buf[BUF_SIZE];
  fscanf(file, "%s %lu\n", buf, &temp->amount_gates);
  if ( strcmp(buf, "[gates]") != 0 ) {
    printf("no [gates]?? '%s' unexpected\n", buf);
    return;
  }
  printf("[gates] %lu\n", temp->amount_gates);

  if ( temp->amount_gates > BUF_SIZE ) {
    fprintf(stderr, "amount_gates > BUF_SIZE");
    fprintf(stderr, "Not enough space to handle all gates");
    fprintf(stderr, "Please split the circuit or increase BUF_SIZE");
    return;
  }


  for (unsigned int i = 0; i < temp->amount_gates; i++) {
    char name[BUF_SIZE];
    char type[BUF_SIZE];

    int x = fscanf(file, "%s %s\n", name, type);

    if ( x == -1 ) {
      // Unexpected end of file
      printf("EOF??\n");
      break;
    }

    struct gate g;

    memmove(g.name, name, BUF_SIZE);
    memmove(g.type, type, BUF_SIZE);

    temp->gates[i] = g;

    printf("[%u] gatename: %s, type: %s\n", i, temp->gates[i].name, temp->gates[i].type);
  }


  // Third should be [wires]
  fscanf(file, "%s %lu\n", buf, &temp->amount_wires);
  if ( strcmp(buf, "[wires]") != 0 ) {
    printf("no [wires]?? '%s' unexpected\n", buf);
    return;
  }
  printf("[wires] %lu\n", temp->amount_wires);

  if ( temp->amount_wires > BUF_SIZE ) {
    fprintf(stderr, "amount_wires > BUF_SIZE");
    fprintf(stderr, "Not enough space to handle all wires");
    fprintf(stderr, "Please split the circuit or increase BUF_SIZE");
    return;
  }


  for (unsigned int i = 0; i < temp->amount_wires; i++) {
    char leftuuid[BUF_SIZE];
    char leftport[BUF_SIZE];
    char rightuuid[BUF_SIZE];
    char rightport[BUF_SIZE];

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
    temp->wires[i] = w;

    printf("leftuuid: %s, leftport: %s, rightuuid: %s, rightport: %s\n", w.leftuuid, w.leftport, w.rightuuid, w.rightport);
  }

}
