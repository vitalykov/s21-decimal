#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_decimal frac_part;
  GetDecimalIntFractionalPart(&value, result, &frac_part);

  return (int)kShortOk;
}
