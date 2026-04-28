#include <limits.h>

#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"
#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_decimal int_part, frac_part;
  GetDecimalIntFractionalPart(&src, &int_part, &frac_part);
  ShortStatus status = kShortOk;
  unsigned sign = GetSign(&src);
  if (int_part.bits[kMidBits] != 0u || int_part.bits[kHighBits] != 0u ||
      (int_part.bits[kLowBits] > (unsigned)INT_MAX && sign == POSITIVE_SIGN) ||
      int_part.bits[kLowBits] > (unsigned)INT_MAX + 1) {
    status = kCalculationError;
  } else {
    *dst = (int)int_part.bits[kLowBits];
    if (GetSign(&src) == NEGATIVE_SIGN) {
      *dst *= -1;
    }
  }

  return (int)status;
}
