#include <stdint.h>

#include "bigbig_lib/bigbig_lib.h"

#define UINT64_RIGHT_HALF_MASK 0x00000000FFFFFFFF
#define INT_BITS 32

void IAddBigBigDecimalBitsToUint(BigBigDecimal *value, unsigned term) {
  unsigned carry = term;
  for (int i = kBigBigLowBits; i <= kBigBigHighBits; ++i) {
    uint64_t sum = (uint64_t)(value->bits[i]) + carry;
    value->bits[i] = (unsigned)(sum & UINT64_RIGHT_HALF_MASK);
    carry = (unsigned)(sum >> INT_BITS);
  }
}
