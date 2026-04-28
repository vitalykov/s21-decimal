#include <limits.h>

#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

START_TEST(zero_conversion) {
  int num = 0;
  s21_decimal got_result;
  const char *expected_result_str = "0";
  int got_status = s21_from_int_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(positive_int_conversion) {
  int num = 123456789;
  s21_decimal got_result;
  const char *expected_result_str = "123456789";
  int got_status = s21_from_int_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(negative_int_conversion) {
  int num = -123456789;
  s21_decimal got_result;
  const char *expected_result_str = "-123456789";
  int got_status = s21_from_int_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(max_int_conversion) {
  int num = INT_MAX;
  s21_decimal got_result;
  const char *expected_result_str = "2147483647";
  int got_status = s21_from_int_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(min_int_conversion) {
  int num = INT_MIN;
  s21_decimal got_result;
  const char *expected_result_str = "-2147483648";
  int got_status = s21_from_int_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(small_positive_conversion) {
  int num = 1;
  s21_decimal got_result;
  const char *expected_result_str = "1";
  int got_status = s21_from_int_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(small_negative_conversion) {
  int num = -1;
  s21_decimal got_result;
  const char *expected_result_str = "-1";
  int got_status = s21_from_int_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

Suite *suite_s21_from_int_to_decimal(void) {
  Suite *suite = suite_create("s21_from_int_to_decimal");
  TCase *tcase_core = tcase_create("core");

  tcase_add_test(tcase_core, zero_conversion);
  tcase_add_test(tcase_core, positive_int_conversion);
  tcase_add_test(tcase_core, negative_int_conversion);
  tcase_add_test(tcase_core, max_int_conversion);
  tcase_add_test(tcase_core, min_int_conversion);
  tcase_add_test(tcase_core, small_positive_conversion);
  tcase_add_test(tcase_core, small_negative_conversion);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
