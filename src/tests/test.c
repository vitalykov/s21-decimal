#include "test.h"

void run_test_suite(Suite *test_suite) {
  SRunner *suite_runner = srunner_create(test_suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  srunner_free(suite_runner);
}

void run_tests(void) {
  Suite *test_suites[] = {suite_s21_add(),
                          suite_s21_sub(),
                          suite_s21_div(),
                          suite_s21_mul(),
                          suite_s21_is_less(),
                          suite_s21_is_less_or_equal(),
                          suite_s21_is_greater(),
                          suite_s21_is_greater_or_equal(),
                          suite_s21_is_equal(),
                          suite_s21_is_not_equal(),
                          suite_s21_from_int_to_decimal(),
                          suite_s21_from_float_to_decimal(),
                          suite_s21_from_decimal_to_int(),
                          suite_s21_from_decimal_to_float(),
                          suite_s21_floor(),
                          suite_s21_truncate(),
                          suite_s21_round(),
                          suite_s21_negate(),
                          NULL};

  for (Suite **test_suite = test_suites; *test_suite != NULL; ++test_suite) {
    run_test_suite(*test_suite);
  }
}

int main(void) {
  run_tests();
  return 0;
}
