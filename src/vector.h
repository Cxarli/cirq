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


// Loop over all items in the vector
#define VEC_EACH(vec, var) \
  for (size_t __i = 0, __last; (void)(__last = (__i == (vec).amount - 1)), __i < (vec).amount; __i++) \
    with(var = (vec).items[__i])


bool vector_push(vector_t *vec, void *item);
void vector_init(vector_t *vec, size_t size);
void vector_free(vector_t *vec);

#endif
