#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"

int CountLeadingZeros(const s21_decimal *value) {
  int clz = 0;
  bool stop = false;
  for (int i = kHighBits; (i >= kLowBits) && !stop; --i) {
    if (value->bits[i] == 0U) {
      clz += INT_BITS;
    } else {
      clz += __builtin_clz(value->bits[i]);
      stop = true;
    }
  }
  return clz;
}
