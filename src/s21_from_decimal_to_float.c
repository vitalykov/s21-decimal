#include <string.h>

#include "big_lib/big_lib.h"
#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"
#include "s21_decimal.h"

#define FLOAT_SIGN_BITS 1
#define FLOAT_SIGN_BITS_START 0
#define FLOAT_SIGN_BITS_END 0

#define FLOAT_EXPONENT_BITS 8
#define FLOAT_EXPONENT_BITS_START 1
#define FLOAT_EXPONENT_BITS_END 8

#define FLOAT_MANTISSA_BITS 23
#define FLOAT_MANTISSA_BITS_START 9
#define FLOAT_MANTISSA_BITS_END 31

#define BIAS 127

#define INT_BITS 32

static void ReverseSetBitsInInterval(unsigned *part, int from, int to,
                                     unsigned num) {
  int temp = to;
  to = (INT_BITS - 1) - from;
  from = (INT_BITS - 1) - temp;
  unsigned mask = ((1U << (to - from + 1)) - 1);
  unsigned num_with_corrected_len = num & mask;
  mask = ~(mask << from);
  *part &= mask;
  *part |= (num_with_corrected_len << from);
}

static void FromDecimalToBinaryFractionalPart(s21_decimal *fractional_part,
                                              unsigned *bin_scaling_factor) {
  *bin_scaling_factor = GetScalingFactor(fractional_part);
  int count_shift = CountLeadingZeros(fractional_part);
  InPlaceLeftShift(fractional_part, count_shift);
  for (unsigned i = 0; i < *bin_scaling_factor; ++i) {
    unsigned remainder;
    InPlaceDivisionByUintRemainder(fractional_part, 5U, &remainder);
  }
  *bin_scaling_factor += count_shift;

  if (*bin_scaling_factor == DECIMAL_BITS) {
    *bin_scaling_factor = 0U;
  }
}

static unsigned CutBitsIntegerPart(s21_decimal *integer_part,
                                   int *len_integer_part_bits, int *exp) {
  unsigned integer_part_bits = 0;
  *len_integer_part_bits = DECIMAL_BITS - CountLeadingZeros(integer_part);

  if (*len_integer_part_bits > 0) {
    *len_integer_part_bits -= 1;

    int len_int_bits_to_cut = *len_integer_part_bits - FLOAT_MANTISSA_BITS;

    if (len_int_bits_to_cut > 0) {
      *len_integer_part_bits -= len_int_bits_to_cut;
      RightShift(*integer_part, len_int_bits_to_cut, integer_part);
      *exp = FLOAT_MANTISSA_BITS + len_int_bits_to_cut;
    } else {
      *exp = *len_integer_part_bits;
    }

    integer_part_bits = integer_part->bits[0];
    integer_part_bits &= ((1U << *len_integer_part_bits) - 1);
  }

  return integer_part_bits;
}

static unsigned CutBitsFractionalPart(s21_decimal *fractional_part,
                                      int *len_fractional_part_bits, int *exp,
                                      unsigned *bin_scaling_factor,
                                      int len_integer_part_bits) {
  unsigned fractional_part_bits = 0;
  int len_frac_bits_to_cut;

  bool integer_is_set = (*exp != -1);

  if (!integer_is_set) {
    *len_fractional_part_bits =
        DECIMAL_BITS - CountLeadingZeros(fractional_part) - 1;
    len_frac_bits_to_cut = *len_fractional_part_bits - FLOAT_MANTISSA_BITS;
  } else {
    *len_fractional_part_bits = *bin_scaling_factor;
    len_frac_bits_to_cut = *len_fractional_part_bits -
                           (FLOAT_MANTISSA_BITS - len_integer_part_bits);
  }

  if (len_frac_bits_to_cut > 0) {
    *bin_scaling_factor -= len_frac_bits_to_cut;
    *len_fractional_part_bits -= len_frac_bits_to_cut;
    InPlaceRightShift(fractional_part, len_frac_bits_to_cut);
  }

  fractional_part_bits = fractional_part->bits[0];
  if (!integer_is_set) {
    fractional_part_bits &= ((1U << *len_fractional_part_bits) - 1);
  }

  if (*len_fractional_part_bits < FLOAT_MANTISSA_BITS - len_integer_part_bits) {
    *bin_scaling_factor += FLOAT_MANTISSA_BITS - *len_fractional_part_bits;
  }

  if (*bin_scaling_factor > FLOAT_MANTISSA_BITS) {
    *exp = FLOAT_MANTISSA_BITS - *bin_scaling_factor;
  }

  if (*exp == -1) {
    *exp = -BIAS;
  }

  return fractional_part_bits;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  unsigned sign = GetSign(&src);
  SetSign(&src, POSITIVE_SIGN);

  s21_decimal integer_part;
  s21_decimal fractional_part;
  GetDecimalIntFractionalPart(&src, &integer_part, &fractional_part);

  unsigned bin_scaling_factor;
  FromDecimalToBinaryFractionalPart(&fractional_part, &bin_scaling_factor);

  unsigned dst_bits = 0;
  int exp = -1;

  int len_integer_part_bits;
  unsigned integer_part_bits =
      CutBitsIntegerPart(&integer_part, &len_integer_part_bits, &exp);
  if (len_integer_part_bits > 0) {
    ReverseSetBitsInInterval(
        &dst_bits, FLOAT_MANTISSA_BITS_START,
        FLOAT_MANTISSA_BITS_START + len_integer_part_bits - 1,
        integer_part_bits);
  }

  int len_fractional_part_bits;
  unsigned fractional_part_bits =
      CutBitsFractionalPart(&fractional_part, &len_fractional_part_bits, &exp,
                            &bin_scaling_factor, len_integer_part_bits);
  if (len_fractional_part_bits > 0) {
    ReverseSetBitsInInterval(&dst_bits,
                             FLOAT_MANTISSA_BITS_START + len_integer_part_bits,
                             FLOAT_MANTISSA_BITS_START + len_integer_part_bits +
                                 len_fractional_part_bits - 1,
                             fractional_part_bits);
  }

  exp += BIAS;

  ReverseSetBitsInInterval(&dst_bits, FLOAT_EXPONENT_BITS_START,
                           FLOAT_EXPONENT_BITS_END, exp);

  ReverseSetBitsInInterval(&dst_bits, FLOAT_SIGN_BITS_START,
                           FLOAT_SIGN_BITS_END, sign);
  memcpy(dst, &dst_bits, sizeof(*dst));
  return (int)kShortOk;
}
