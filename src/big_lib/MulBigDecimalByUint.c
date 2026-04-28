
#include <limits.h>
#include <stdint.h>

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

void MulBigDecimalBitsByUint(const BigDecimal *value, unsigned int factor,
                             BigDecimal *result) {
  SetNullBigDecimal(result);
  result->bits[kBigSignScalingBits] = value->bits[kBigSignScalingBits];

  unsigned int decades = 0;
  for (int i = kBigLowBits; i <= kBigHighBits; ++i) {
    uint64_t current =
        ((uint64_t)value->bits[i]) * ((uint64_t)factor) + decades;
    result->bits[i] = (unsigned int)(current & UINT64_RIGHT_HALF_MASK);
    decades = (unsigned int)(current >> INT_BITS);
  }
}
