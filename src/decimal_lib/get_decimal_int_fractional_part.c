#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"

#define DECIMAL_MAX_DIGITS 29

void GetDecimalIntFractionalPart(const s21_decimal *value,
                                 s21_decimal *int_part,
                                 s21_decimal *frac_part) {
  DecimalCopy(*value, int_part);
  unsigned int frac_digits[DECIMAL_MAX_DIGITS];

  int n = (int)GetScalingFactor(value);
  for (int i = 0; i < n; ++i) {
    InPlaceDivisionByUintRemainder(int_part, 10u, frac_digits + i);
  }
  SetScalingFactor(int_part, 0u);

  SetNull(frac_part);
  frac_part->bits[kSignScalingPart] = value->bits[kSignScalingPart];
  for (int i = n - 1; i >= 0; --i) {
    InPlaceMultiplyIntDecimalByUint(frac_part, 10u);
    InPlaceAddIntDecimalToUint(frac_part, frac_digits[i]);
  }
}
