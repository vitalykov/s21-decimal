#include <limits.h>

#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

START_TEST(positive_int_conversion) {
  NEW_DECIMAL(decimal, "123456");

  int got_result;
  int got_status = s21_from_decimal_to_int(decimal, &got_result);
  int expected_status = TEST_CONVERSION_OK;
  int expected_result = 123456;

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_int_eq(expected_result, got_result);
}
END_TEST

START_TEST(negative_int_conversion) {
  NEW_DECIMAL(decimal, "-123456");

  int got_result;
  int got_status = s21_from_decimal_to_int(decimal, &got_result);
  int expected_status = TEST_CONVERSION_OK;
  int expected_result = -123456;

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_int_eq(expected_result, got_result);
}
END_TEST

START_TEST(zero_conversion) {
  NEW_DECIMAL(decimal, "0");

  int got_result;
  int got_status = s21_from_decimal_to_int(decimal, &got_result);
  int expected_status = TEST_CONVERSION_OK;
  int expected_result = 0;

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_int_eq(expected_result, got_result);
}
END_TEST

START_TEST(max_int_conversion) {
  char max_int_str[20];
  sprintf(max_int_str, "%d", INT_MAX);
  NEW_DECIMAL(decimal, max_int_str);

  int got_result;
  int got_status = s21_from_decimal_to_int(decimal, &got_result);
  int expected_status = TEST_CONVERSION_OK;
  int expected_result = INT_MAX;

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_int_eq(expected_result, got_result);
}
END_TEST

START_TEST(min_int_conversion) {
  char min_int_str[20];
  sprintf(min_int_str, "%d", (int)INT_MIN);
  NEW_DECIMAL(decimal, min_int_str);

  int got_result;
  int got_status = s21_from_decimal_to_int(decimal, &got_result);
  int expected_status = TEST_CONVERSION_OK;
  int expected_result = INT_MIN;

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_int_eq(expected_result, got_result);
}
END_TEST

START_TEST(rounding_down_conversion) {
  NEW_DECIMAL(decimal, "123.456");

  int got_result;
  int got_status = s21_from_decimal_to_int(decimal, &got_result);
  int expected_status = TEST_CONVERSION_OK;
  int expected_result = 123;

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_int_eq(expected_result, got_result);
}
END_TEST

START_TEST(overflow_conversion) {
  char overflow_str[30];
  sprintf(overflow_str, "%lld", (long long)INT_MAX + 1);
  NEW_DECIMAL(decimal, overflow_str);

  int got_result;
  int got_status = s21_from_decimal_to_int(decimal, &got_result);
  int expected_status = TEST_CONVERSION_ERROR;

  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(underflow_conversion) {
  char underflow_str[30];
  sprintf(underflow_str, "%lld", (long long)INT_MIN - 1);
  NEW_DECIMAL(decimal, underflow_str);

  int got_result;
  int got_status = s21_from_decimal_to_int(decimal, &got_result);
  int expected_status = TEST_CONVERSION_ERROR;

  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(large_number_conversion) {
  NEW_DECIMAL(decimal, "123456000.0");

  int got_result;
  int got_status = s21_from_decimal_to_int(decimal, &got_result);
  int expected_status = TEST_CONVERSION_OK;
  int expected_result = 123456000;

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_int_eq(expected_result, got_result);
}
END_TEST

START_TEST(very_small_number) {
  NEW_DECIMAL(decimal, "0.000123");

  int got_result;
  int got_status = s21_from_decimal_to_int(decimal, &got_result);
  int expected_status = TEST_CONVERSION_OK;
  int expected_result = 0;

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_int_eq(expected_result, got_result);
}
END_TEST

Suite *suite_s21_from_decimal_to_int(void) {
  Suite *suite = suite_create("s21_from_decimal_to_int");
  TCase *tcase_core = tcase_create("core");

  tcase_add_test(tcase_core, positive_int_conversion);
  tcase_add_test(tcase_core, negative_int_conversion);
  tcase_add_test(tcase_core, zero_conversion);
  tcase_add_test(tcase_core, max_int_conversion);
  tcase_add_test(tcase_core, min_int_conversion);
  tcase_add_test(tcase_core, rounding_down_conversion);
  tcase_add_test(tcase_core, overflow_conversion);
  tcase_add_test(tcase_core, underflow_conversion);
  tcase_add_test(tcase_core, large_number_conversion);
  tcase_add_test(tcase_core, very_small_number);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
