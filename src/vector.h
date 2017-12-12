#ifndef VECTOR_H
#define VECTOR_H


#include <stdlib.h>

#include "defines.h"
#include "bool.h"


typedef struct vector {
  size_t amount;
  void* items[BUF_SIZE];
} vector_t;


bool vector_push(vector_t *vec, void *item);

#endif
