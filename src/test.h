#ifndef TEST_H
#define TEST_H


#include <stdio.h>
#include <stdbool.h>


#define failstr(x) { \
  ++__fails; \
  fprintf(stderr, "[FAIL] %s:%i    %s\n", __FILE__, __LINE__, x); \
}


#define fail() \
  failstr("EXPLICITLY");


#define assert_true(x) \
  if (! (x)) \
    failstr(#x " != true");


#define assert_false(x) \
  if ((x)) \
    failstr(#x " != false");


#define assert_eq(x, y) \
  if ((x) != (y)) \
    failstr(#x " != " #y);


#define assert_neq(x, y) \
  if ((x) == (y)) \
    failstr(#x " == " #y);


#define TEST(func) { \
  ++__tests; \
  \
  unsigned int __fails = func(); \
  if (__fails != 0) ++__failed_tests; \
  \
  if (__fails == 0) { \
    printf("[ OK ] " #func "\n"); \
  } \
}


#define TEST_START \
  unsigned int __fails = 0; \


#define TEST_END \
  return __fails; \


#define TESTS_START \
  printf("\nStarting tests...\n\n"); \
  unsigned int __tests = 0, __failed_tests = 0; \


#define TESTS_RESULT \
  printf("\n\nTests done. %i / %i success\n", __tests - __failed_tests, __tests); \


unsigned int test_nand(void);
unsigned int test_nor(void);
unsigned int test_xand(void);
unsigned int test_xor(void);

unsigned int test_half_adder(void);
unsigned int test_full_adder(void);

unsigned int test_not_loop(void);


#endif
