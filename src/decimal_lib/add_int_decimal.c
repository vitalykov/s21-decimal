#include <stdint.h>

#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"

LongStatus InPlaceAddIntDecimal(s21_decimal *value, s21_decimal term) {
  LongStatus s = kLongOk;

  unsigned value_sign = GetSign(value);
  unsigned term_sign = GetSign(&term);
  if (value_sign == term_sign) {
    unsigned carry = 0u;
    for (int i = kLowBits; i <= kHighBits; ++i) {
      uint64_t sum = (uint64_t)(value->bits[i]) + term.bits[i];
      value->bits[i] = (unsigned)(sum & UINT64_RIGHT_HALF_MASK) + carry;
      carry = (unsigned)(sum >> INT_BITS);
    }

    if (carry != 0) {
      if (GetSign(value) == POSITIVE_SIGN) {
        s = kNumberTooLarge;
      } else {
        s = kNumberTooSmall;
      }
    }
  } else {
    if (value_sign == NEGATIVE_SIGN) {
      SwapDecimal(value, &term);
    }
    SetSign(&term, POSITIVE_SIGN);
    s = InPlaceSubtractIntDecimal(value, term);
  }

  return s;
}
