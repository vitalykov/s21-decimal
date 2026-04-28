#include <stdbool.h>

#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

bool EqualZeroBigDecimal(const BigDecimal *value) {
  bool result = true;
  for (int i = kBigLowBits; i <= kBigHighBits; ++i) {
    if (value->bits[i] != 0U) {
      result = false;
    }
  }

  return result;
}
