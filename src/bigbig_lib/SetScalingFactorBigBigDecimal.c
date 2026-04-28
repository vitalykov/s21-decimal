#include "bigbig_lib/bigbig_lib.h"

void SetScalingFactorBigBigDecimal(BigBigDecimal *value,
                                   unsigned scaling_factor) {
  value->bits[kBigBigScalingBits] = scaling_factor;
}
