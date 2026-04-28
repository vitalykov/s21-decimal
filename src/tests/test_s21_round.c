#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

#define MAX_DECIMAL_STR_SIZE 32

START_TEST(test_round_positive_round_down) {
  const char *num_str = "123.456";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "123";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_round(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(test_round_positive_round_up) {
  const char *num_str = "123.567";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "124";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_round(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(test_round_negative_round_down) {
  const char *num_str = "-123.456";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "-123";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_round(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(test_round_negative_round_up) {
  const char *num_str = "-123.567";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "-124";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_round(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(test_round_midpoint_even) {
  const char *num_str = "123.5";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "124";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_round(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(test_round_zero) {
  const char *num_str = "0.000";
  NEW_DECIMAL(num, num_str);

  const char *expected_result_str = "0";
  int expected_status = 0;

  s21_decimal got_result;
  int got_status = s21_round(num, &got_result);

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

Suite *suite_s21_round(void) {
  Suite *suite = suite_create("s21_round");
  TCase *tcase_core = tcase_create("core");

  tcase_add_test(tcase_core, test_round_positive_round_down);
  tcase_add_test(tcase_core, test_round_positive_round_up);
  tcase_add_test(tcase_core, test_round_negative_round_down);
  tcase_add_test(tcase_core, test_round_negative_round_up);
  tcase_add_test(tcase_core, test_round_midpoint_even);
  tcase_add_test(tcase_core, test_round_zero);

  suite_add_tcase(suite, tcase_core);
  return suite;
}
