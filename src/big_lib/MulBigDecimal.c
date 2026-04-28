#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

void MulBigDecimal(const BigDecimal *value, const BigDecimal *factor,
                   BigDecimal *result) {
  MulBigDecimalBits(value, factor, result);
  SetScalingFactorBigDecimal(result, GetScalingFactorBigDecimal(value) +
                                         GetScalingFactorBigDecimal(factor));
  RemoveTrailingZerosBigDecimal(result);
}
