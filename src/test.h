#ifndef TEST_H
#define TEST_H


#include <stdio.h>
#include <stdbool.h>


#define failstr(x) { \
  ++fails; \
  fprintf(stderr, "[FAIL] " x "\n"); \
}


#define fail() \
  failstr("EXPLICITLY");


#define assert_true(x) \
  if (! (x)) \
    failstr(#x " is not true");


#define assert_false(x) \
  if ((x)) \
    failstr(#x " is not false");


#define assert_eq(x, y) \
  if ((x) != (y)) \
    failstr(#x " != " #y);


#define assert_neq(x, y) \
  if ((x) == (y)) \
    failstr(#x " == " #y);


#define TEST(func) { \
  ++tests; \
  unsigned int f = func(); \
  failed_tests += (f == 0) ? 0 : 1; \
  if (f == 0) { \
    printf("[ OK ] " #func "\n"); \
  } \
}


#define TEST_START \
  unsigned int fails = 0; \


#define TEST_END \
  return fails; \


#define TESTS_START \
  printf("\nStarting tests...\n\n"); \
  unsigned int tests = 0, failed_tests = 0; \


#define TESTS_RESULT \
  printf("\n\nTests done. %i / %i success\n", tests - failed_tests, tests); \


unsigned int test_nand(void);
unsigned int test_nor(void);
unsigned int test_xand(void);
unsigned int test_xor(void);

unsigned int test_half_adder(void);
unsigned int test_full_adder(void);

unsigned int test_not_loop(void);


#endif
