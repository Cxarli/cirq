#include "vector.h"

#include "assert.h"
#include "benchmark.h"


bool vector_push(vector_t *vec, void *item) {
	FUNC_START();

	assert_not_null(vec);

	// NOTE: Blocks vectors from containing NULL
	assert_not_null(item);

	// Check for overflow
	if (vec->amount == vec->size - 1) {
		panic("Overflowing vector!");
		FUNC_END();
		return false;
	}

	// Add item
	vec->items[vec->amount] = item;

	// Increase counter
	vec->amount++;

	FUNC_END();
	return true;
}


void vector_init(vector_t *vec, size_t size) {
	vec->amount = 0;
	vec->size = size;


	vec->items = malloc(size * sizeof(void*));

	// Set all fields to zero (clear array)
	memset(vec->items, 0, size * sizeof(void*));
}


void vector_free(vector_t *vec) {
	assert_not_null(vec);

	free(vec->items);
}
