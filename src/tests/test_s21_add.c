#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

START_TEST(basic_int) {
  const char *num1_str = "1234567891234567";
  const char *num2_str = "12234";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "1234567891246801";
  int got_status = s21_add(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(basic_float) {
  const char *num1_str = "1234567891234.567";
  const char *num2_str = "12234.4";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "1234567903468.967";
  int got_status = s21_add(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(overflow) {
  const char *num1_str = "79228162514264337593543950334";
  const char *num2_str = "4";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  int got_status = s21_add(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_LARGE;

  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(decimal_too_small) {
  const char *num1_str = "-79228162514264337593543950334";
  const char *num2_str = "-4";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  int got_status = s21_add(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_SMALL;

  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

Suite *suite_s21_add(void) {
  Suite *suite = suite_create("s21_add");
  TCase *tcase_core = tcase_create("core of s21_add");

  tcase_add_test(tcase_core, basic_int);
  tcase_add_test(tcase_core, basic_float);
  tcase_add_test(tcase_core, overflow);
  tcase_add_test(tcase_core, decimal_too_small);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

// gcc -o 21tests *.c decimal_lib/*.c big_lib/*.c bigbig_lib/*.c tests/*.c -I.
// -I/opt/homebrew/opt/check/include -L/opt/homebrew/opt/check/lib -lcheck
