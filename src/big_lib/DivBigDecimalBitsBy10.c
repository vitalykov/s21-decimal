#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

void DivBigDecimalBitsBy10(const BigDecimal *value, BigDecimal *result,
                           unsigned int *remainder) {
  DivBigDecimalBitsByUint(value, 10u, result, remainder);
}
