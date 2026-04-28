#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

#define MAX_DECIMAL_STR_SIZE 32

START_TEST(test_truncate_positive_with_fraction) {
  const char *num_str = "79228162514264337.93423423";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "79228162514264337";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_truncate(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(test_truncate_negative_with_fraction) {
  const char *num_str = "-79228162514264337.93423423";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "-79228162514264337";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_truncate(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(test_truncate_positive_integer) {
  const char *num_str = "3169126500";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "3169126500";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_truncate(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(test_truncate_small_positive) {
  const char *num_str = "0.999999999";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "0";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_truncate(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(test_truncate_small_negative) {
  const char *num_str = "-0.999999999";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "-0";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_truncate(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(test_truncate_zero) {
  const char *num_str = "0.000000000";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "0";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_truncate(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

Suite *suite_s21_truncate(void) {
  Suite *suite = suite_create("s21_truncate");
  TCase *tcase_core = tcase_create("core of s21_truncate");

  tcase_add_test(tcase_core, test_truncate_positive_with_fraction);
  tcase_add_test(tcase_core, test_truncate_negative_with_fraction);
  tcase_add_test(tcase_core, test_truncate_positive_integer);
  tcase_add_test(tcase_core, test_truncate_small_positive);
  tcase_add_test(tcase_core, test_truncate_small_negative);
  tcase_add_test(tcase_core, test_truncate_zero);

  suite_add_tcase(suite, tcase_core);
  return suite;
}
