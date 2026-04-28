#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

START_TEST(less_or_equal_positive_float_less) {
  const char *num1_str = "12345.6789";
  const char *num2_str = "12345.6790";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less_or_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_or_equal_positive_float_equal) {
  const char *num1_str = "12345.6789";
  const char *num2_str = "12345.6789";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less_or_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_or_equal_negative_float_less) {
  const char *num1_str = "-12345.6790";
  const char *num2_str = "-12345.6789";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less_or_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_or_equal_mixed_sign_negative_less) {
  const char *num1_str = "-12345.6789";
  const char *num2_str = "12345.6789";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less_or_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_or_equal_max_values) {
  const char *num1_str = "79228162514264337593543950334";
  const char *num2_str = "79228162514264337593543950335";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less_or_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_or_equal_zero_positive) {
  const char *num1_str = "0.00000000";
  const char *num2_str = "0.00000001";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less_or_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_or_equal_different_scale) {
  const char *num1_str = "123.45000";
  const char *num2_str = "123.45";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less_or_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_or_equal_small_numbers) {
  const char *num1_str = "0.000000001";
  const char *num2_str = "0.000000002";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less_or_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_or_equal_equal_numbers) {
  const char *num1_str = "123456789.987654321";
  const char *num2_str = "123456789.987654321";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less_or_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(less_or_equal_greater_number) {
  const char *num1_str = "987654321.123456789";
  const char *num2_str = "123456789.987654321";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_less_or_equal(num1, num2);
  ck_assert_int_eq(result, false);
}
END_TEST

Suite *suite_s21_is_less_or_equal(void) {
  Suite *suite = suite_create("s21_is_less_or_equal");
  TCase *tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, less_or_equal_positive_float_less);
  tcase_add_test(tcase_core, less_or_equal_positive_float_equal);
  tcase_add_test(tcase_core, less_or_equal_negative_float_less);
  tcase_add_test(tcase_core, less_or_equal_mixed_sign_negative_less);
  tcase_add_test(tcase_core, less_or_equal_max_values);
  tcase_add_test(tcase_core, less_or_equal_zero_positive);
  tcase_add_test(tcase_core, less_or_equal_different_scale);
  tcase_add_test(tcase_core, less_or_equal_small_numbers);
  tcase_add_test(tcase_core, less_or_equal_equal_numbers);
  tcase_add_test(tcase_core, less_or_equal_greater_number);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
