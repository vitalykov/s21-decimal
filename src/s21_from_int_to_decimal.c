#include <stdint.h>

#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"
#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  SetNull(dst);
  int64_t long_src = (int64_t)src;
  if (long_src < 0) {
    SetSign(dst, NEGATIVE_SIGN);
    long_src = -long_src;
  }
  dst->bits[kLowBits] = (unsigned)((uint64_t)long_src & UINT64_RIGHT_HALF_MASK);

  return (int)kShortOk;
}
