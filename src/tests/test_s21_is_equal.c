#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

START_TEST(equal_positive_int) {
  const char *num_str = "123456789";
  NEW_DECIMAL(num1, num_str);
  NEW_DECIMAL(num2, num_str);

  int result = s21_is_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(equal_negative_int) {
  const char *num_str = "-123456789";
  NEW_DECIMAL(num1, num_str);
  NEW_DECIMAL(num2, num_str);

  int result = s21_is_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(equal_positive_float) {
  const char *num_str = "1234.56789";
  NEW_DECIMAL(num1, num_str);
  NEW_DECIMAL(num2, num_str);

  int result = s21_is_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(equal_negative_float) {
  const char *num_str = "-1234.56789";
  NEW_DECIMAL(num1, num_str);
  NEW_DECIMAL(num2, num_str);

  int result = s21_is_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(equal_zero) {
  const char *num_str = "0";
  NEW_DECIMAL(num1, num_str);
  NEW_DECIMAL(num2, num_str);

  int result = s21_is_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(equal_positive_and_negative_zero) {
  const char *num1_str = "0";
  const char *num2_str = "-0";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(not_equal_positive_int) {
  const char *num1_str = "123456789";
  const char *num2_str = "987654321";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_equal(num1, num2);
  ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(not_equal_negative_int) {
  const char *num1_str = "-123456789";
  const char *num2_str = "-987654321";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_equal(num1, num2);
  ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(not_equal_different_scales) {
  const char *num1_str = "123.456";  // scale 3
  const char *num2_str = "123456";   // scale 0
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_equal(num1, num2);
  ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(not_equal_different_signs) {
  const char *num1_str = "123.456";
  const char *num2_str = "-123.456";
  NEW_DECIMAL(num1, num1_str);
  NEW_DECIMAL(num2, num2_str);

  int result = s21_is_equal(num1, num2);
  ck_assert_int_eq(result, false);
}
END_TEST

START_TEST(equal_max_decimal) {
  const char *num_str = "79228162514264337593543950335";  // MAX_DECIMAL
  NEW_DECIMAL(num1, num_str);
  NEW_DECIMAL(num2, num_str);

  int result = s21_is_equal(num1, num2);
  ck_assert_int_eq(result, true);
}
END_TEST

Suite *suite_s21_is_equal(void) {
  Suite *suite = suite_create("s21_is_equal");
  TCase *tcase_core = tcase_create("core of s21_is_equal");

  tcase_add_test(tcase_core, equal_positive_int);
  tcase_add_test(tcase_core, equal_negative_int);
  tcase_add_test(tcase_core, equal_positive_float);
  tcase_add_test(tcase_core, equal_negative_float);
  tcase_add_test(tcase_core, equal_zero);
  tcase_add_test(tcase_core, equal_positive_and_negative_zero);
  tcase_add_test(tcase_core, not_equal_positive_int);
  tcase_add_test(tcase_core, not_equal_negative_int);
  tcase_add_test(tcase_core, not_equal_different_scales);
  tcase_add_test(tcase_core, not_equal_different_signs);
  tcase_add_test(tcase_core, equal_max_decimal);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
