#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"
#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  DecimalCopy(value, result);
  unsigned int remainder = 0;

  int n = (int)GetScalingFactor(&value);
  for (int i = 0; i < n; ++i) {
    InPlaceDivisionByUintRemainder(result, 10u, &remainder);
  }
  SetScalingFactor(result, 0u);

  if (remainder >= 5u) {
    unsigned result_sign = GetSign(result);
    SetSign(result, POSITIVE_SIGN);
    InPlaceAddIntDecimalToUint(result, 1u);
    SetSign(result, result_sign);
  }

  return (int)kShortOk;
}
