
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

#define SIGN_START_BIT 31
#define END_BIT 31
#define SCALING_FACTOR_START_BIT 16
#define SCALING_FACTOR_END_BIT 24

// bits[0] --- bits[5] contain the low, middle, and high 32 bits of
// the 192-bit integer, respectively.
//
//
//
// bits[6] contains the scaling factor and
// sign and consists of the following parts:

// Bits 0 through 15, the lower word, are unused and must be zero.
// Bits 16 to !!!!24!!!! must contain an exponent between 0 and 28, indicating
// the power of 10 to divide the integer. Bits 24 through 30 are unused and must
// be zero. Bit 31 contains the sign; 0 is positive and 1 is negative.

void SubBigDecimalBits(const BigDecimal *value_1, const BigDecimal *value_2,
                       BigDecimal *result) {
  SetNullBigDecimal(result);
  result->bits[kBigSignScalingBits] = value_1->bits[kBigSignScalingBits];
  unsigned int borrow = 0;

  for (int i = kBigLowBits; i <= kBigHighBits; ++i) {
    uint64_t current = 0;
    uint64_t v1 = (uint64_t)value_1->bits[i];
    uint64_t v2 = (uint64_t)value_2->bits[i] + borrow;
    if (v1 < v2) {
      current = (v1 + ((uint64_t)1 << INT_BITS)) - v2;
      borrow = 1;
    } else {
      current = v1 - v2;
      borrow = 0;
    }
    result->bits[i] = (unsigned int)(current & UINT64_RIGHT_HALF_MASK);
  }
}
