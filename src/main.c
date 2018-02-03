#include "test.h"

#ifdef BENCH
	#include <stdlib.h>
	#include "benchmark.h"
#endif


int main(int argc, char *argv[]) {

	#ifdef BENCH
		bench_prepare();
		atexit(bench_write_states);
	#endif

	return (int) test_all(argc, argv);
}
