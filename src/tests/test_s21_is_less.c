#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

START_TEST(less_positive_int) {
  const char *num1_str = "123456789";
  const char *num2_str = "987654321";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_negative_int) {
  const char *num1_str = "-987654321";
  const char *num2_str = "-123456789";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_positive_float) {
  const char *num1_str = "12345.6789";
  const char *num2_str = "12345.6790";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_negative_float) {
  const char *num1_str = "-12345.6790";
  const char *num2_str = "-12345.6789";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_mixed_sign) {
  const char *num1_str = "-12345.6789";
  const char *num2_str = "12345.6789";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(not_less_equal) {
  const char *num1_str = "123456789";
  const char *num2_str = "123456789";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(not_less_greater) {
  const char *num1_str = "987654321";
  const char *num2_str = "123456789";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(less_different_scale) {
  const char *num1_str = "12345.6789";
  const char *num2_str = "1234567.89";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_small_numbers) {
  const char *num1_str = "0.000000001";
  const char *num2_str = "0.000000002";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_max_values) {
  const char *num1_str = "79228162514264337593543950334";
  const char *num2_str = "79228162514264337593543950335";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_min_values) {
  const char *num1_str = "-79228162514264337593543950335";
  const char *num2_str = "-79228162514264337593543950334";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_zero_positive) {
  const char *num1_str = "0";
  const char *num2_str = "0.00000001";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_zero_negative) {
  const char *num1_str = "-0.00000001";
  const char *num2_str = "0";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_special_case1) {
  const char *num1_str = "0.999999999";
  const char *num2_str = "1.0";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_special_case2) {
  const char *num1_str = "-1.0";
  const char *num2_str = "-0.999999999";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

Suite *suite_s21_is_less(void) {
  Suite *suite = suite_create("s21_is_less");
  TCase *tcase_core = tcase_create("core of s21_is_less");

  tcase_add_test(tcase_core, less_positive_int);
  tcase_add_test(tcase_core, less_negative_int);
  tcase_add_test(tcase_core, less_positive_float);
  tcase_add_test(tcase_core, less_negative_float);
  tcase_add_test(tcase_core, less_mixed_sign);
  tcase_add_test(tcase_core, not_less_equal);
  tcase_add_test(tcase_core, not_less_greater);
  tcase_add_test(tcase_core, less_different_scale);
  tcase_add_test(tcase_core, less_small_numbers);
  tcase_add_test(tcase_core, less_max_values);
  tcase_add_test(tcase_core, less_min_values);
  tcase_add_test(tcase_core, less_zero_positive);
  tcase_add_test(tcase_core, less_zero_negative);
  tcase_add_test(tcase_core, less_special_case1);
  tcase_add_test(tcase_core, less_special_case2);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
