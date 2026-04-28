#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

#define BIG_DECIMAL_MAX_DIGITS 58

void GetBigDecimalIntFractionalPart(const BigDecimal *value,
                                    BigDecimal *int_part,
                                    BigDecimal *frac_part) {
  BigDecimalCopy(value, int_part);
  unsigned int frac_digits[BIG_DECIMAL_MAX_DIGITS];

  int n = (int)GetScalingFactorBigDecimal(value);
  for (int i = 0; i < n; ++i) {
    IDivBigDecimalBitsBy10(int_part, frac_digits + i);
  }
  SetScalingFactorBigDecimal(int_part, 0u);

  SetNullBigDecimal(frac_part);
  frac_part->bits[kBigSignScalingBits] = value->bits[kBigSignScalingBits];
  for (int i = n - 1; i >= 0; --i) {
    IMulBigDecimalBitsBy10(frac_part);
    IAddBigDecimalBitsToUint(frac_part, frac_digits[i]);
  }
}
