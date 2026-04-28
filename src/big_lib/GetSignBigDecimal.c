#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

unsigned int GetSignBigDecimal(const BigDecimal *value) {
  return value->bits[kBigSignScalingBits] >> (INT_BITS - 1);
}
