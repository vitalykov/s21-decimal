#include <stdint.h>

#include "bigbig_lib/bigbig_lib.h"

#define INT_BITS 32

static void IDivBigBigDecimalBitsByUint(BigBigDecimal *dividend,
                                        unsigned int divisor,
                                        unsigned int *remainder) {
  unsigned rem = 0u;
  for (int i = kBigBigHighBits; i >= kBigBigLowBits; --i) {
    uint64_t part = (uint64_t)dividend->bits[i] + ((uint64_t)rem << INT_BITS);
    dividend->bits[i] = part / divisor;
    rem = (unsigned int)(part % divisor);
  }

  if (remainder != NULL) {
    *remainder = rem;
  }
}

void IDivBigBigDecimalBitsBy10(BigBigDecimal *value, unsigned *remainder) {
  IDivBigBigDecimalBitsByUint(value, 10u, remainder);
}
