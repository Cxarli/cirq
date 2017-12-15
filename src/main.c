#include <string.h> // strcmp

#include "test.h"
#include "defines.h"


int main(int argc, char *argv[]) {
  TESTS_START;

  // If no tests specified, run some default tests
  if (argc == 1) {
    TEST(test_nand);
    TEST(test_nor);
    TEST(test_xand);
    TEST(test_xor);
  }

  for (int i=1; i < argc; i++) {
    switch_str(argv[i]) {
      case_str("nand") {
        TEST(test_nand);
      }

      else case_str("nor") {
        TEST(test_nor);
      }

      else case_str("xand") {
        TEST(test_xand);
      }

      else case_str("xor") {
        TEST(test_xor);
      }

      else case_str("full_adder") {
        printf("\nBe prepared for errors...\n");
        TEST(test_full_adder);
      }

      else case_str("not_loop") {
        TEST(test_not_loop);
      }
    }
  }

  TESTS_RESULT;
  return (int) failed_tests;
}
