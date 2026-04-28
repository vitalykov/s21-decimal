#include <stdint.h>

#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"

LongStatus InPlaceSubtractIntDecimal(s21_decimal *result,
                                     s21_decimal subtrahend) {
  LongStatus s = kLongOk;

  unsigned result_sign = GetSign(result);
  unsigned subtrahend_sign = GetSign(&subtrahend);
  if (result_sign == subtrahend_sign) {
    if (LessIntDecimal(*result, subtrahend)) {
      SwapDecimal(result, &subtrahend);
    }

    unsigned carry = 0u;
    for (int i = kLowBits; i <= kHighBits; ++i) {
      unsigned sub = result->bits[i] - carry - subtrahend.bits[i];
      if (sub > result->bits[i]) {
        carry = 1u;
      } else {
        carry = 0u;
      }
      result->bits[i] = sub;
    }
  } else {
    SetSign(&subtrahend, !subtrahend_sign);
    InPlaceAddIntDecimal(result, subtrahend);
  }

  return s;
}
