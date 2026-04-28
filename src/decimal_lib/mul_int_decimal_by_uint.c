#include <stdint.h>

#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"

LongStatus InPlaceMultiplyIntDecimalByUint(s21_decimal *value,
                                           unsigned factor) {
  LongStatus s = kLongOk;
  unsigned carry = 0;
  for (int i = kLowBits; i <= kHighBits; ++i) {
    uint64_t product = (uint64_t)(value->bits[i]) * factor;
    value->bits[i] = (unsigned)(product & UINT64_RIGHT_HALF_MASK) + carry;
    carry = (unsigned)(product >> INT_BITS);
  }

  if (carry != 0) {
    value->bits[kSignScalingPart] += carry;
    if (GetSign(value) == POSITIVE_SIGN) {
      s = kNumberTooLarge;
    } else {
      s = kNumberTooSmall;
    }
  }

  return s;
}
