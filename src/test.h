#include <stdio.h>

#define failstr(x) fprintf(stderr, "FAILED: " x "\n");

#define fail() \
  failstr("EXPLICITLY");

#define assert_true(x) \
  if (! (x)) { \
    failstr( #x " is not true"); \
  }

#define assert_false(x) \
  if (x) { \
    failstr(#x " is not false"); \
  }

#define assert_eq(x, y) \
  if ((x) != (y)) { \
    failstr(#x " != " #y); \
  }

#define assert_neq(x, y) \
  if ((x) == (y)) { \
    failstr(#x " == " #y); \
  }
