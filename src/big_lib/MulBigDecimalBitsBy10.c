#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

void MulBigDecimalBitsBy10(const BigDecimal *value, BigDecimal *result) {
  MulBigDecimalBitsByUint(value, 10u, result);
}
