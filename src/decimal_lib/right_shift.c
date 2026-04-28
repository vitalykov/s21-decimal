#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"
#include "util.h"

LongStatus InPlaceRightShift(s21_decimal *value, int shift) {
  if (shift >= DECIMAL_BITS) {
    value->bits[kLowBits] = 0U;
    value->bits[kMidBits] = 0U;
    value->bits[kHighBits] = 0U;
    shift = 0;
  }

  if (shift > 0) {
    int current_shift = Min(shift, INT_BITS - 1);
    int remained_shift = shift - current_shift;
    unsigned *bits = value->bits;
    bits[kLowBits] >>= current_shift;
    bits[kLowBits] += GetLowestBits(bits[kMidBits], current_shift)
                      << (INT_BITS - current_shift);
    bits[kMidBits] >>= current_shift;
    bits[kMidBits] += GetLowestBits(bits[kHighBits], current_shift)
                      << (INT_BITS - current_shift);
    bits[kHighBits] >>= current_shift;

    InPlaceRightShift(value, remained_shift);
  }

  return kLongOk;
}

LongStatus RightShift(s21_decimal value, int shift, s21_decimal *result) {
  DecimalCopy(value, result);
  LongStatus s = InPlaceRightShift(result, shift);

  return s;
}
