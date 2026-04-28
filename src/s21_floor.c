#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"
#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal frac_part;
  GetDecimalIntFractionalPart(&value, result, &frac_part);
  if (!EqualZeroDecimal(frac_part)) {
    unsigned result_sign = GetSign(result);
    if (result_sign == NEGATIVE_SIGN) {
      SetSign(result, POSITIVE_SIGN);
      InPlaceAddIntDecimalToUint(result, 1u);
      SetSign(result, result_sign);
    }
  }

  return (int)kShortOk;
}
