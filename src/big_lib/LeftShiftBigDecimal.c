#include "big_lib/big_lib.h"
#include "big_lib/defs.h"
#include "util.h"

void LeftShiftBigDecimal(const BigDecimal *value, int shift,
                         BigDecimal *result) {
  BigDecimalCopy(value, result);

  while (shift > 0) {
    int current_shift = Min(shift, INT_BITS - 1);
    shift -= current_shift;
    unsigned int *bits = result->bits;
    for (int i = kBigHighBits; i > kBigLowBits; --i) {
      bits[i] <<= current_shift;
      bits[i] += GetHighestBits(bits[i - 1], current_shift);
    }
    bits[kBigLowBits] <<= current_shift;
  }
}
