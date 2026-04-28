#include <stdbool.h>

#include "bigbig_lib/bigbig_lib.h"

#define INT_BITS 32

int CountLeadingZerosBigBigDecimal(const BigBigDecimal *value) {
  int clz = 0;
  bool stop = false;
  for (int i = kBigBigHighBits; (i >= kBigBigLowBits) && !stop; --i) {
    if (value->bits[i] == 0U) {
      clz += INT_BITS;
    } else {
      clz += __builtin_clz(value->bits[i]);
      stop = true;
    }
  }
  return clz;
}
