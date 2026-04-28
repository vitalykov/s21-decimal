#include <stdbool.h>

#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

int CountLeadingZerosBigDecimal(const BigDecimal *value) {
  int clz = 0;
  bool stop = false;
  for (int i = kBigHighBits; (i >= kBigLowBits) && !stop; --i) {
    if (value->bits[i] == 0U) {
      clz += INT_BITS;
    } else {
      clz += __builtin_clz(value->bits[i]);
      stop = true;
    }
  }
  return clz;
}
