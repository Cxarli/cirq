#ifndef VECTOR_H
#define VECTOR_H


#include <stdlib.h>
#include <stdbool.h>

#include "defines.h"


typedef struct vector {
  size_t amount;
  size_t size;
  void** items;
} vector_t;


bool vector_push(vector_t *vec, void *item);

void vector_init(vector_t *vec, size_t size);

#endif
