#include <stdint.h>

#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

void AddBigDecimalBitsToUint(const BigDecimal *value, unsigned int term,
                             BigDecimal *result) {
  SetNullBigDecimal(result);
  result->bits[kBigSignScalingBits] = value->bits[kBigSignScalingBits];

  unsigned carry = term;
  for (int i = kBigLowBits; i <= kBigHighBits; ++i) {
    uint64_t sum = (uint64_t)(value->bits[i]) + carry;
    result->bits[i] = (unsigned)(sum & UINT64_RIGHT_HALF_MASK);
    carry = (unsigned)(sum >> INT_BITS);
  }
}
