#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"
#include "util.h"

LongStatus InPlaceLeftShift(s21_decimal *value, int shift) {
  LongStatus s = kLongOk;

  if (shift >= DECIMAL_BITS) {
    value->bits[kLowBits] = 0U;
    value->bits[kMidBits] = 0U;
    value->bits[kHighBits] = 0U;
    shift = 0;
    s = kNumberTooLarge;
  }

  if (shift > 0) {
    int current_shift = Min(shift, INT_BITS - 1);
    int remained_shift = shift - current_shift;
    unsigned *bits = value->bits;
    bits[kHighBits] <<= current_shift;
    bits[kHighBits] += GetHighestBits(bits[kMidBits], current_shift);
    bits[kMidBits] <<= current_shift;
    bits[kMidBits] += GetHighestBits(bits[kLowBits], current_shift);
    bits[kLowBits] <<= current_shift;

    InPlaceLeftShift(value, remained_shift);
  }

  return s;
}
