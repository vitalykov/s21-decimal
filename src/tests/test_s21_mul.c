#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

START_TEST(basic_int) {
  const char *num1_str = "792281625";
  const char *num2_str = "4";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "3169126500";
  int got_status = s21_mul(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(basic_float) {
  const char *num1_str = "987654321.56789";
  const char *num2_str = "0.1234";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "121876543.281477626";
  int got_status = s21_mul(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(negative) {
  const char *num1_str = "-1234555.5";
  const char *num2_str = "-12345.1234";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "15240739991.6487";
  int got_status = s21_mul(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(mixed_sign) {
  const char *num1_str = "123456789.987654321";
  const char *num2_str = "-987654321.123456789";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "-121932632103337905.66209419311";
  int got_status = s21_mul(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(overflow_small) {
  const char *num1_str = "-79228162514264337593543950334";
  const char *num2_str = "4";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  int got_status = s21_mul(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_SMALL;

  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(overflow_large) {
  const char *num1_str = "79228162514264337593543950334";
  const char *num2_str = "4";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  int got_status = s21_mul(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_LARGE;
  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(mul_by_zero) {
  const char *num1_str = "-79228162514264337593543950334";
  const char *num2_str = "0";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "0";
  int got_status = s21_mul(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;
  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_str_eq(expected_result_str, got_result_str);
  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(mul_by_one) {
  const char *num1_str = "123456789.987654321";
  const char *num2_str = "1";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "123456789.987654321";
  int got_status = s21_mul(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;
  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_str_eq(expected_result_str, got_result_str);
  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(small_numbers) {
  const char *num1_str = "0.000000001";
  const char *num2_str = "0.000000001";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "0.000000000000000001";
  int got_status = s21_mul(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;
  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(edge_case_max) {
  const char *num1_str = "79228162514264337593543950335";
  const char *num2_str = "1";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "79228162514264337593543950335";
  int got_status = s21_mul(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;
  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_str_eq(expected_result_str, got_result_str);
  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(edge_case_min) {
  const char *num1_str = "-79228162514264337593543950335";
  const char *num2_str = "1";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "-79228162514264337593543950335";
  int got_status = s21_mul(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;
  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_str_eq(expected_result_str, got_result_str);
  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(precision_handling) {
  const char *num1_str = "1.0000000000000000000000000001";
  const char *num2_str = "1.0000000000000000000000000001";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "1.0000000000000000000000000002";
  int got_status = s21_mul(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;
  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

Suite *suite_s21_mul(void) {
  Suite *suite = suite_create("s21_mul");
  TCase *tcase_core = tcase_create("core of s21_mul");

  tcase_add_test(tcase_core, basic_int);
  tcase_add_test(tcase_core, basic_float);
  tcase_add_test(tcase_core, negative);
  tcase_add_test(tcase_core, mixed_sign);
  tcase_add_test(tcase_core, overflow_small);
  tcase_add_test(tcase_core, overflow_large);
  tcase_add_test(tcase_core, mul_by_zero);
  tcase_add_test(tcase_core, mul_by_one);
  tcase_add_test(tcase_core, small_numbers);
  tcase_add_test(tcase_core, edge_case_max);
  tcase_add_test(tcase_core, edge_case_min);
  tcase_add_test(tcase_core, precision_handling);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
