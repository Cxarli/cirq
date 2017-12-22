#include "utils.h"

#include <stdio.h>
#include <unistd.h>

#include "assert.h"
#include "benchmark.h"


// Redirect stdout to stderr
void STDOUT_TO_STDERR(void) {
	fflush(stdout);
	dup2(2, 1);
}


// Reset the redirection from stdout to stderr
void RESET_STDOUT(void) {
	fflush(stderr);
	dup2(1, 1);
}


circuit_t *find_dependency(vector_t *dependencies, char *name) {
	FUNC_START();

	assert_not_null(name);

	if (dependencies == NULL) {
		goto notfound;
	}


	for (size_t i = 0; i < dependencies->amount; i++) {
		circuit_t *dep = dependencies->items[i];

		if (strcmp(dep->name, name) == 0) {
			FUNC_END();
			return dep;
		}
	}


	notfound:
	warn("Failed to find dependency");
	FUNC_END();
	return NULL;
}
