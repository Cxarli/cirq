#include "vector.h"


bool vector_push(vector_t *vec, void *item) {
  // Check for overflow
  if (vec->amount == BUF_SIZE - 1) {
    return false;
  }

  // Add item
  vec->items[vec->amount] = item;

  // Increase counter
  vec->amount++;

  return true;
}
