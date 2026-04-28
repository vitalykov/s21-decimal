#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"
#include "s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal sub_result;
  s21_sub(value_1, value_2, &sub_result);

  return EqualZeroDecimal(sub_result) || GetSign(&sub_result) == POSITIVE_SIGN;
}
