#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  DecimalCopy(value, result);
  SetSign(result, !GetSign(&value));

  return (int)kShortOk;
}
