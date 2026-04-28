#include "big_lib/big_lib.h"
#include "big_lib/defs.h"
#include "util.h"

void RightShiftBigDecimal(const BigDecimal *value, int shift,
                          BigDecimal *result) {
  BigDecimalCopy(value, result);

  while (shift > 0) {
    int current_shift = Min(shift, INT_BITS - 1);
    shift -= current_shift;
    unsigned *bits = result->bits;
    for (int i = kBigLowBits; i < kBigHighBits; ++i) {
      bits[i] >>= current_shift;
      bits[i] += GetLowestBits(bits[i + 1], current_shift)
                 << (INT_BITS - current_shift);
    }
    bits[kBigHighBits] >>= current_shift;
  }
}
