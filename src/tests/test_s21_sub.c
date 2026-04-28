#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

START_TEST(basic_int) {
  const char *num1_str = "79228162514264337593543950334";
  const char *num2_str = "7593543950334";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "79228162514264330000000000000";
  int got_status = s21_sub(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(basic_float) {
  const char *num1_str = "7922816251426433.759354395";
  const char *num2_str = "2514264.659354395";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "7922816248912169.1";
  int got_status = s21_sub(num1, num2, &got_result);
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
  const char *expected_result_str = "-1222210.3766";
  int got_status = s21_sub(num1, num2, &got_result);
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
  const char *expected_result_str = "1111111111.11111111";
  int got_status = s21_sub(num1, num2, &got_result);
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
  int got_status = s21_sub(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_SMALL;

  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(overflow_large) {
  const char *num1_str = "79228162514264337593543950334";
  const char *num2_str = "-4";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  int got_status = s21_sub(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_LARGE;

  ck_assert_int_eq(expected_status, got_status);
}
END_TEST

START_TEST(sub_zero) {
  const char *num1_str = "123456789.987654321";
  const char *num2_str = "0";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "123456789.987654321";
  int got_status = s21_sub(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(sub_from_zero) {
  const char *num1_str = "0";
  const char *num2_str = "123456789.987654321";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "-123456789.987654321";
  int got_status = s21_sub(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(small_numbers) {
  const char *num1_str = "0.000000001";
  const char *num2_str = "0.00000000002";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "0.00000000098";
  int got_status = s21_sub(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(inverse_small_numbers) {
  const char *num1_str = "0.00000000002";
  const char *num2_str = "0.000000001";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "-0.00000000098";
  int got_status = s21_sub(num1, num2, &got_result);
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
  const char *expected_result_str = "79228162514264337593543950334";
  int got_status = s21_sub(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(precision_handling) {
  const char *num1_str = "1.0000000000000000000000000001";
  const char *num2_str = "0.0000000000000000000000000001";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "1";
  int got_status = s21_sub(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

START_TEST(equal_numbers) {
  const char *num1_str = "123456789.987654321";
  const char *num2_str = "123456789.987654321";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  s21_decimal got_result;
  const char *expected_result_str = "0";
  int got_status = s21_sub(num1, num2, &got_result);
  int expected_status = TEST_ARITHMETIC_OK;

  char got_result_str[MAX_DECIMAL_STR_SIZE];
  FromDecimalToString(got_result, got_result_str);

  ck_assert_int_eq(expected_status, got_status);
  ck_assert_str_eq(expected_result_str, got_result_str);
}
END_TEST

Suite *suite_s21_sub(void) {
  Suite *suite = suite_create("s21_sub");
  TCase *tcase_core = tcase_create("core of s21_sub");

  tcase_add_test(tcase_core, basic_int);
  tcase_add_test(tcase_core, basic_float);
  tcase_add_test(tcase_core, negative);
  tcase_add_test(tcase_core, mixed_sign);
  tcase_add_test(tcase_core, overflow_small);
  tcase_add_test(tcase_core, overflow_large);
  tcase_add_test(tcase_core, sub_zero);
  tcase_add_test(tcase_core, sub_from_zero);
  tcase_add_test(tcase_core, small_numbers);
  tcase_add_test(tcase_core, inverse_small_numbers);
  tcase_add_test(tcase_core, edge_case_max);
  tcase_add_test(tcase_core, precision_handling);
  tcase_add_test(tcase_core, equal_numbers);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
