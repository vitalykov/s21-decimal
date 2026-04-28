#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

int LenInt(int num) {
  int len = 0;
  while (num != 0) {
    num /= 10;
    ++len;
  }
  return len;
}

void RemoveTrailingZerosFromStr(char *str) {
  if (strchr(str, '.') != NULL) {
    int len = strlen(str);
    while (len > 0 && str[len - 1] == '0') {
      str[--len] = '\0';
    }
    if (len > 0 && str[len - 1] == '.') {
      str[--len] = '\0';
    }
  }
}

void FormatFloatString(char *buffer, float num) {
  sprintf(buffer, "%.*f", 7 - LenInt((int)num), num);

  RemoveTrailingZerosFromStr(buffer);

  char *dot_pos = strchr(buffer, '.');
  if (dot_pos != NULL && *(dot_pos + 1) == '\0') {
    *dot_pos = '\0';
  }
}

START_TEST(zero_float_conversion) {
  float num = 0.0f;
  s21_decimal got_result;
  char expected_result_str[MAX_DECIMAL_STR_SIZE];
  FormatFloatString(expected_result_str, num);

  int got_status = s21_from_float_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(positive_float_conversion) {
  float num = 123.456f;
  s21_decimal got_result;
  char expected_result_str[MAX_DECIMAL_STR_SIZE];
  FormatFloatString(expected_result_str, num);

  int got_status = s21_from_float_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(negative_float_conversion) {
  float num = -123.456f;
  s21_decimal got_result;
  char expected_result_str[MAX_DECIMAL_STR_SIZE];
  FormatFloatString(expected_result_str, num);

  int got_status = s21_from_float_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(small_negative_float_conversion) {
  float num = -0.000123f;
  s21_decimal got_result;
  char expected_result_str[MAX_DECIMAL_STR_SIZE];
  FormatFloatString(expected_result_str, num);

  int got_status = s21_from_float_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(max_float_conversion) {
  float num = FLT_MAX;
  s21_decimal got_result;
  int got_status = s21_from_float_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_ERROR;

  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(min_float_conversion) {
  float num = FLT_MIN;
  s21_decimal got_result;

  int got_status = s21_from_float_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_ERROR;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(nan_conversion) {
  float num = NAN;
  s21_decimal got_result;
  int got_status = s21_from_float_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_ERROR;

  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(inf_conversion) {
  float num = INFINITY;
  s21_decimal got_result;
  int got_status = s21_from_float_to_decimal(num, &got_result);
  int expected_status = TEST_CONVERSION_ERROR;

  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

Suite *suite_s21_from_float_to_decimal(void) {
  Suite *suite = suite_create("s21_from_float_to_decimal");
  TCase *tcase_core = tcase_create("core");

  tcase_add_test(tcase_core, zero_float_conversion);
  tcase_add_test(tcase_core, positive_float_conversion);
  tcase_add_test(tcase_core, negative_float_conversion);
  tcase_add_test(tcase_core, small_negative_float_conversion);
  tcase_add_test(tcase_core, max_float_conversion);
  tcase_add_test(tcase_core, min_float_conversion);
  tcase_add_test(tcase_core, nan_conversion);
  tcase_add_test(tcase_core, inf_conversion);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
