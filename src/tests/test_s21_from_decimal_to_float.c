#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"
#include "tests/test.h"

START_TEST(integer_positive) {
  NEW_DECIMAL(dec, "12345");
  float got = 0;
  s21_from_decimal_to_float(dec, &got);
  float expected = 12345.0f;

  ck_assert_float_eq_tol(expected, got, 7);
}
END_TEST

START_TEST(integer_negative) {
  NEW_DECIMAL(dec, "-67890");
  float got = 0;
  s21_from_decimal_to_float(dec, &got);
  float expected = -67890.0f;

  ck_assert_float_eq_tol(expected, got, 7);
}
END_TEST

START_TEST(simple_fraction) {
  NEW_DECIMAL(dec, "123.456");
  float got = 0;
  s21_from_decimal_to_float(dec, &got);
  float expected = 123.456f;

  ck_assert_float_eq_tol(expected, got, 7);
}
END_TEST

START_TEST(small_fraction) {
  NEW_DECIMAL(dec, "0.000789");
  float got = 0;
  s21_from_decimal_to_float(dec, &got);
  float expected = 0.000789f;

  ck_assert_float_eq_tol(expected, got, 7);
}
END_TEST

START_TEST(zero_test) {
  NEW_DECIMAL(dec, "0");
  float got = 0;
  s21_from_decimal_to_float(dec, &got);
  float expected = 0.0f;

  ck_assert_float_eq_tol(expected, got, 7);
}
END_TEST

START_TEST(one_test) {
  NEW_DECIMAL(dec, "1");
  float got = 0;
  s21_from_decimal_to_float(dec, &got);
  float expected = 1.0f;

  ck_assert_float_eq_tol(expected, got, 7);
}
END_TEST

START_TEST(large_with_fraction) {
  NEW_DECIMAL(dec, "9876543.21");
  float got = 0;
  s21_from_decimal_to_float(dec, &got);
  float expected = 9876543.21f;

  ck_assert_float_eq_tol(expected, got, 7);
}
END_TEST

START_TEST(power_of_two) {
  NEW_DECIMAL(dec, "8388608");  // 2^23
  float got = 0;
  s21_from_decimal_to_float(dec, &got);
  float expected = 8388608.0f;

  ck_assert_float_eq_tol(expected, got, 7);
}
END_TEST

Suite *suite_s21_from_decimal_to_float(void) {
  Suite *s = suite_create("s21_from_decimal_to_float");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, integer_positive);
  tcase_add_test(tc, integer_negative);
  tcase_add_test(tc, simple_fraction);
  tcase_add_test(tc, small_fraction);
  tcase_add_test(tc, zero_test);
  tcase_add_test(tc, one_test);
  tcase_add_test(tc, large_with_fraction);
  tcase_add_test(tc, power_of_two);

  suite_add_tcase(s, tc);
  return s;
}
