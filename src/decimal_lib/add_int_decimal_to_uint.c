#include <stdint.h>

#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"

LongStatus InPlaceAddIntDecimalToUint(s21_decimal *value, unsigned term) {
  LongStatus s = kLongOk;
  unsigned carry = term;
  for (int i = kLowBits; i <= kHighBits; ++i) {
    uint64_t sum = (uint64_t)(value->bits[i]) + carry;
    value->bits[i] = (unsigned)(sum & UINT64_RIGHT_HALF_MASK);
    carry = (unsigned)(sum >> INT_BITS);
  }

  if (carry != 0) {
    if (GetSign(value) == POSITIVE_SIGN) {
      s = kNumberTooLarge;
    } else {
      s = kNumberTooSmall;
    }
  }

  return s;
}
