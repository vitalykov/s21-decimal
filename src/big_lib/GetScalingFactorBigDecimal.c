
#include <limits.h>
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

unsigned GetScalingFactorBigDecimal(const BigDecimal *value) {
  unsigned int power = 0;
  for (int i = SCALING_FACTOR_START_BIT; i < SCALING_FACTOR_END_BIT; ++i) {
    power |= ((value->bits[kBigSignScalingBits] >> i & 1)
              << (i - SCALING_FACTOR_START_BIT));
  }
  return power;
}
