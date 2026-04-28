#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

int LenBigDecimal(const BigDecimal *value) {
  int len = 0;

  BigDecimal value_copy;
  BigDecimalCopy(value, &value_copy);

  while (!EqualZeroBigDecimal(&value_copy)) {
    unsigned remainder;
    IDivBigDecimalBitsBy10(&value_copy, &remainder);
    ++len;
  }

  return len;
}
