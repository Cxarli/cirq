#ifndef BENCHMARK_H
#define BENCHMARK_H


#define FUNC_START() \
	time_t start = time();

#define FUNC_END() \
	time_t end = time(); \
	BENCH_ADD(__FUNCTION__, end - start);


#endif
