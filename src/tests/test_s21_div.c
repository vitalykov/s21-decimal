#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

START_TEST(basic_int) {
  const char *num1_str = "222214748364";
  const char *num2_str = "4";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "55553687091";
  int got_status = s21_div(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(basic_float) {
  const char *num1_str = "2222.14748364";
  const char *num2_str = "22.44";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "99.02618019786096256684491979";
  int got_status = s21_div(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(tricky_float) {
  const char *num1_str = "7.9228162514264337593543950325";
  const char *num2_str = "10";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "0.7922816251426433759354395032";
  int got_status = s21_div(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(basic_ints_float_res) {
  const char *num1_str = "2222147483647";
  const char *num2_str = "1000000000000";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "2.222147483647";
  int got_status = s21_div(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(both_negative) {
  const char *num1_str = "-21474836472";
  const char *num2_str = "-1234";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "17402622.748784440842787682334";
  int got_status = s21_div(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(dividend_negative) {
  const char *num1_str = "-21474836472";
  const char *num2_str = "1234";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "-17402622.748784440842787682334";
  int got_status = s21_div(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(very_small_num) {
  const char *num1_str = "0.000000000000001231231231232";
  const char *num2_str = "12341231231";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "0.0000000000000000000000000998";
  int got_status = s21_div(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(divider_negative) {
  const char *num1_str = "21474836472";
  const char *num2_str = "-1234";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "-17402622.748784440842787682334";
  int got_status = s21_div(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(overflow) {
  const char *num1_str = "-79228162514264337593543950334";
  const char *num2_str = "0.5";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  int got_status = s21_div(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_SMALL;

  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(div_by_zero) {
  const char *num1_str = "79228162514264337593543950334";
  const char *num2_str = "0";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  int got_status = s21_div(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_DIV_ZERO;

  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

Suite *suite_s21_div(void) {
  Suite *suite = suite_create("s21_div");
  TCase *tcase_core = tcase_create("core of s21_div");

  tcase_add_test(tcase_core, basic_int);
  tcase_add_test(tcase_core, basic_float);
  tcase_add_test(tcase_core, tricky_float);
  tcase_add_test(tcase_core, basic_ints_float_res);
  tcase_add_test(tcase_core, both_negative);
  tcase_add_test(tcase_core, dividend_negative);
  tcase_add_test(tcase_core, divider_negative);
  tcase_add_test(tcase_core, very_small_num);
  tcase_add_test(tcase_core, overflow);
  tcase_add_test(tcase_core, div_by_zero);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
