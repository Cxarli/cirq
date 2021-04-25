#ifndef TEST_H
#define TEST_H


#include <stdio.h>
#include <stdbool.h>

#include "color.h"


typedef struct test_result {
	unsigned int fails;
	unsigned int total;
} test_result_t;


#define failstr(x) { \
	++__test.fails; \
	fprintf(stderr, C_RED "[FAIL] %s:%i" C_RESET_FG " \t%s\n", __FILE__, __LINE__, x); \
}


#define fail() \
	failstr("EXPLICITLY");


#define assert(x, str) \
	++__test.total; \
	if (! (x)) \
		failstr(str);


#define assert_true(x) \
	assert((x), #x " != true")

#define assert_false(x) \
	assert(!(x), #x " != false")

#define assert_eq(x, y) \
	assert((x) == (y), #x " != " #y)

#define assert_neq(x, y) \
	assert((x) != (y), #x " == " #y)

#define assert_not_null(x) \
	assert((x) != NULL, #x " is NULL")

#define assert_str_eq(x, y) \
	assert(strcmp((x), (y)) == 0, #x " != " #y)

#define assert_str_neq(x, y) \
	assert(strcmp((x), (y)) != 0, #x " != " #y)


#define TEST_START \
	test_result_t __test = { .total = 0, .fails = 0 }; \


#define TEST_END \
	return __test;



#define TEST(func) { \
	test_result_t __result = func(); \
	__failed_tests += __result.fails; \
	__tests += __result.total; \
	\
	if (__result.fails == 0) { \
		printf(C_GREEN "[ OK ] " #func "\n" C_RESET_FG); \
	} \
}


#define TESTS_START \
	printf(C_LIGHT_BLUE "\nStarting tests...\n\n" C_RESET_FG); \
	unsigned int __tests = 0, __failed_tests = 0; \


#define TESTS_RESULT \
	printf(C_LIGHT_BLUE "\n\nTests done. %i / %i tests successful\n\n" C_RESET_FG, __tests - __failed_tests, __tests); \



unsigned int test_all(int argc, char *argv[]);


test_result_t test_nand(void);
test_result_t test_nor(void);
test_result_t test_xand(void);
test_result_t test_xor(void);

test_result_t test_half_adder(void);
test_result_t test_full_adder(void);

test_result_t test_not_loop(void);
test_result_t test_nested(void);


#endif
