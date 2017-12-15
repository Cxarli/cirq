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
  failed_tests += (func() == 0) ? 0 : 1; \
}

#define TEST_START \
  unsigned int fails = 0; \

#define TEST_END \
  return fails; \

#define TESTS_START \
  printf("\n\nStarting tests...\n"); \
  unsigned int tests = 0, failed_tests = 0; \

#define TESTS_RESULT \
  printf("\n\nTests done. %i / %i success\n", tests - failed_tests, tests); \


unsigned int test_nand(void);
unsigned int test_not_loop(void);
unsigned int test_xor(void);
unsigned int test_full_adder(void);
