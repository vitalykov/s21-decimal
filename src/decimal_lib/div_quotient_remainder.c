#include <stdbool.h>
#include <string.h>

#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"

LongStatus InPlaceDivisionByUintRemainder(s21_decimal *dividend,
                                          unsigned divisor,
                                          unsigned *remainder) {
  LongStatus s = kLongOk;
  s21_decimal subtrahend;
  // TODO: replace with int_to_decimal
  SetNull(&subtrahend);
  subtrahend.bits[0] = divisor;
  SetSign(&subtrahend, GetSign(dividend));
  s21_decimal quotient;
  SetNull(&quotient);
  s21_decimal count;
  // TODO: replace by int_to_decimal
  SetNull(&count);
  count.bits[0] = 1u;
  bool stop = false;

  while (!LessIntDecimal(*dividend, subtrahend) && !stop) {
    InPlaceSubtractIntDecimal(dividend, subtrahend);
    InPlaceAddIntDecimal(&quotient, count);
    stop = (CountLeadingZeros(&subtrahend) == 0);
    if (!stop) {
      InPlaceLeftShift(&subtrahend, 1);
      InPlaceLeftShift(&count, 1);
    }
  }

  while (!EqualZeroDecimal(*dividend) && !EqualZeroDecimal(count)) {
    if (!LessIntDecimal(*dividend, subtrahend)) {
      InPlaceSubtractIntDecimal(dividend, subtrahend);
      InPlaceAddIntDecimal(&quotient, count);
    }
    InPlaceRightShift(&subtrahend, 1);
    InPlaceRightShift(&count, 1);
  }

  *remainder = dividend->bits[kLowBits];
  SetSign(&quotient, GetSign(dividend));
  DecimalCopy(quotient, dividend);

  return s;
}
