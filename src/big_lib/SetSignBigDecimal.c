#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

#define CLEAR_SIGN_MASK 0x7FFFFFFFu

void SetSignBigDecimal(BigDecimal *value, unsigned int sign) {
  value->bits[kBigSignScalingBits] &= CLEAR_SIGN_MASK;
  value->bits[kBigSignScalingBits] |= (sign << (INT_BITS - 1));
}
