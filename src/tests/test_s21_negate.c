#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

#define MAX_DECIMAL_STR_SIZE 32

START_TEST(test_negate_positive) {
  const char *num_str = "123.456";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "-123.456";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_negate(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(test_negate_negative) {
  const char *num_str = "-123.456";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "123.456";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_negate(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(test_negate_zero) {
  const char *num_str = "0";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "-0";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_negate(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(test_negate_max_positive) {
  const char *num_str = "79228162514264337593543950335";  // MAX_DECIMAL
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "-79228162514264337593543950335";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_negate(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(test_negate_min_negative) {
  const char *num_str = "-79228162514264337593543950335";  // MIN_DECIMAL
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "79228162514264337593543950335";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_negate(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

Suite *suite_s21_negate(void) {
  Suite *suite = suite_create("s21_negate");
  TCase *tcase_core = tcase_create("core");

  tcase_add_test(tcase_core, test_negate_positive);
  tcase_add_test(tcase_core, test_negate_negative);
  tcase_add_test(tcase_core, test_negate_zero);
  tcase_add_test(tcase_core, test_negate_max_positive);
  tcase_add_test(tcase_core, test_negate_min_negative);

  suite_add_tcase(suite, tcase_core);
  return suite;
}
