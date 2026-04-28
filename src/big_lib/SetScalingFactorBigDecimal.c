#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

#define NULL_SCALING_FACTOR_MASK 0xFE00FFFFu
#define SCALING_BITS_START 16

void SetScalingFactorBigDecimal(BigDecimal *value,
                                unsigned int scaling_factor) {
  value->bits[kBigSignScalingBits] &= NULL_SCALING_FACTOR_MASK;
  value->bits[kBigSignScalingBits] |= (scaling_factor << SCALING_BITS_START);
}
