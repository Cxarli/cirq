#include "test.h"


int main() {
  TESTS_START;

  TEST(test_nand);
  TEST(test_not_loop);

  TESTS_RESULT;
}
