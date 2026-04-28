#include "bigbig_lib/bigbig_lib.h"

unsigned int GetScalingFactorBigBigDecimal(const BigBigDecimal *value) {
  return value->bits[kBigBigScalingBits];
}
