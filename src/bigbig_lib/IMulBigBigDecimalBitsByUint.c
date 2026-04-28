#include <stdint.h>

#include "bigbig_lib/bigbig_lib.h"

#define UINT64_RIGHT_HALF_MASK 0x00000000FFFFFFFF
#define INT_BITS 32

void IMulBigBigDecimalBitsByUint(BigBigDecimal *value, unsigned int factor) {
  unsigned int decades = 0;
  for (int i = 0; i <= kBigBigHighBits; ++i) {
    uint64_t current =
        ((uint64_t)value->bits[i]) * ((uint64_t)factor) + decades;
    value->bits[i] = (unsigned int)(current & UINT64_RIGHT_HALF_MASK);
    decades = (unsigned int)((current >> 32) & UINT64_RIGHT_HALF_MASK);
  }
}
