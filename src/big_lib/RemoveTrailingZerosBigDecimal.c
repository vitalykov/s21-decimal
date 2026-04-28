#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

void RemoveTrailingZerosBigDecimal(BigDecimal *value) {
  int scaling_factor = GetScalingFactorBigDecimal(value);
  unsigned last_digit = 0u;
  while (last_digit == 0u && scaling_factor >= 0) {
    --scaling_factor;
    IDivBigDecimalBitsBy10(value, &last_digit);
  }
  IMulBigDecimalBitsBy10(value);
  IAddBigDecimalBitsToUint(value, last_digit);
  SetScalingFactorBigDecimal(value, (unsigned)(scaling_factor + 1));
}
