#include <stddef.h>
#include <stdint.h>

#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

void DivBigDecimalBitsByUint(const BigDecimal *dividend, unsigned int divisor,
                             BigDecimal *result, unsigned int *remainder) {
  SetNullBigDecimal(result);
  result->bits[kBigSignScalingBits] = dividend->bits[kBigSignScalingBits];

  unsigned rem = 0u;
  for (int i = kBigHighBits; i >= kBigLowBits; --i) {
    uint64_t part = (uint64_t)dividend->bits[i] + ((uint64_t)rem << INT_BITS);
    result->bits[i] = part / divisor;
    rem = (unsigned int)(part % divisor);
  }

  if (remainder != NULL) {
    *remainder = rem;
  }
}
