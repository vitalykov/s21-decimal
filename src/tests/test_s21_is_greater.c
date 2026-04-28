#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

START_TEST(greater_positive_int) {
  const char *num1_str = "987654321";
  const char *num2_str = "123456789";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(greater_negative_int) {
  const char *num1_str = "-123456789";
  const char *num2_str = "-987654321";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(greater_positive_float) {
  const char *num1_str = "1234.56789";
  const char *num2_str = "123.456789";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(greater_negative_float) {
  const char *num1_str = "-123.456789";
  const char *num2_str = "-1234.56789";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(greater_equal_numbers) {
  const char *num1_str = "123456789";
  const char *num2_str = "123456789";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(greater_zero_comparison) {
  const char *num1_str = "0";
  const char *num2_str = "0";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(greater_positive_zero_vs_negative_zero) {
  const char *num1_str = "0";
  const char *num2_str = "-0";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(greater_large_numbers) {
  const char *num1_str = "79228162514264337593543950335";  // MAX_DECIMAL
  const char *num2_str = "1";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(greater_small_numbers) {
  const char *num1_str = "0.00000001";
  const char *num2_str = "0.000000001";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(greater_different_scales) {
  const char *num1_str = "123.456";  // scale 3
  const char *num2_str = "123456";   // scale 0
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_greater(num1, num2);
  ck_assert_int_eq(result, false);
}
END_TEST

Suite *suite_s21_is_greater(void) {
  Suite *suite = suite_create("s21_is_greater");
  TCase *tcase_core = tcase_create("core of s21_is_greater");

  tcase_add_test(tcase_core, greater_positive_int);
  tcase_add_test(tcase_core, greater_negative_int);
  tcase_add_test(tcase_core, greater_positive_float);
  tcase_add_test(tcase_core, greater_negative_float);
  tcase_add_test(tcase_core, greater_equal_numbers);
  tcase_add_test(tcase_core, greater_zero_comparison);
  tcase_add_test(tcase_core, greater_positive_zero_vs_negative_zero);
  tcase_add_test(tcase_core, greater_large_numbers);
  tcase_add_test(tcase_core, greater_small_numbers);
  tcase_add_test(tcase_core, greater_different_scales);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
