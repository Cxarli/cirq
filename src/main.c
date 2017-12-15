#include <string.h> // strcmp

#include "test.h"
#include "defines.h"


int main(int argc, char *argv[]) {
  TESTS_START;

  // If no tests specified, run the NAND and XOR test
  if (argc == 1) {
    TEST(test_nand);
    TEST(test_xor);
  }

  for (int i=1; i < argc; i++) {
    switch_str(argv[i]) {
      case_str("nand") {
        TEST(test_nand);
      }

      else case_str("not_loop") {
        TEST(test_not_loop);
      }

      else case_str("xor") {
        TEST(test_xor);
      }
    }
  }

  TESTS_RESULT;
  return (int) failed_tests;
}
