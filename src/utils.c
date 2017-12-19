#include "utils.h"

#include <stdio.h>
#include <unistd.h>



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
