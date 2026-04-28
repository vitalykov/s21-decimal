#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "big_lib/big_lib.h"
#include "bigbig_lib/bigbig_lib.h"
#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"

#define FLOAT_SIGN_BITS 1
#define FLOAT_EXPONENT_BITS 8
#define FLOAT_MANTISSA_BITS 23
#define BIAS 127

#define FLOAT_PRECISION 7

#define DECIMAL_POS_MIN powf(10.0, -28)
#define DECIMAL_POS_MAX powf(2.0, 96) - 1

struct NumParts {
  bool sign;
  unsigned int exponent;
  unsigned int mantissa;
};
typedef struct NumParts NumParts;

static unsigned FloatToBits(const float f) {
  unsigned bits = 0;
  memcpy(&bits, &f, sizeof(float));
  return bits;
}

NumParts ParsePartsOfFloat(float num) {
  unsigned num_bits = FloatToBits(num);

  bool sign =
      ((num_bits >> (FLOAT_EXPONENT_BITS + FLOAT_MANTISSA_BITS)) & 1) != 0;
  unsigned int exponent =
      (num_bits >> (FLOAT_MANTISSA_BITS)) & ((1U << FLOAT_EXPONENT_BITS) - 1);
  unsigned long mantissa = num_bits & ((1U << FLOAT_MANTISSA_BITS) - 1);

  NumParts num_parts = {
      .sign = sign, .exponent = exponent, .mantissa = mantissa};

  return num_parts;
}

#define SIGN_START_BIT 31
#define SIGN_END_BIT 31
#define SCALING_FACTOR_START_BIT 16
#define SCALING_FACTOR_END_BIT 23

static bool GetFloatSign(const NumParts *num_parts) { return num_parts->sign; }

static int CalcBinExp(const NumParts *num_parts) {
  int bin_exp = 0;
  if (num_parts->exponent == 0) {
    bin_exp = 1 - BIAS;
  } else {
    bin_exp = num_parts->exponent - BIAS;
  }
  return bin_exp;
}

static void SetDecimalIntegerPart(s21_decimal *dst, const NumParts *num_parts) {
  int bin_exp = CalcBinExp(num_parts);
  unsigned int integer_part = 0U;
  unsigned int remaining_bin_pow = 0U;
  if (bin_exp >= 0) {
    if (bin_exp > FLOAT_MANTISSA_BITS) {
      integer_part = num_parts->mantissa;
      if (num_parts->exponent != 0) {
        integer_part |= (1U << FLOAT_MANTISSA_BITS);
      }
      remaining_bin_pow = bin_exp - FLOAT_MANTISSA_BITS;
    } else {
      integer_part = ((num_parts->mantissa >> (FLOAT_MANTISSA_BITS - bin_exp)) &
                      ((1U << bin_exp) - 1));
      if (num_parts->exponent != 0) {
        integer_part |= (1U << bin_exp);
      }
    }
  }
  s21_from_int_to_decimal(integer_part, dst);
  InPlaceLeftShift(dst, remaining_bin_pow);
}

static void SetDecimalFractionalPart(s21_decimal *dst,
                                     const NumParts *num_parts) {
  int bin_exp = CalcBinExp(num_parts);
  unsigned int fractional_part = 0;
  if (bin_exp >= 0) {
    if (bin_exp <= FLOAT_MANTISSA_BITS) {
      fractional_part =
          (num_parts->mantissa & ((1U << (FLOAT_MANTISSA_BITS - bin_exp)) - 1));
    }
  } else {
    fractional_part = num_parts->mantissa;
    fractional_part |= (1U << FLOAT_MANTISSA_BITS);
  }
  BigBigDecimal fractional_part_big_big_dec = {0};
  fractional_part_big_big_dec.bits[0] = fractional_part;
  int len_fractional_part = FLOAT_MANTISSA_BITS - bin_exp;
  for (int i = 0; i < len_fractional_part; ++i) {
    IMulBigBigDecimalBitsByUint(&fractional_part_big_big_dec, 5);
  }
  SetScalingFactorBigBigDecimal(&fractional_part_big_big_dec,
                                len_fractional_part);

  s21_decimal fractional_part_dec;
  FromBigBigDecimalToDecimal(fractional_part_big_big_dec, &fractional_part_dec);
  s21_add(*dst, fractional_part_dec, dst);
  RemoveTrailingZeros(dst);
}

static void LosePrecision(s21_decimal *num) {
  // ubludstvo
  int len_to_cut = LenDecimal(num) - FLOAT_PRECISION;
  int len_integer_part = LenDecimal(num) - GetScalingFactor(num);
  unsigned remainder = 0;
  for (int i = 0; i < len_to_cut; ++i) {
    InPlaceDivisionByUintRemainder(num, 10U, &remainder);
  }
  if (remainder >= 5) {
    InPlaceAddIntDecimalToUint(num, 1U);
  }
  for (int i = 0; i < len_integer_part - FLOAT_PRECISION; ++i) {
    InPlaceMultiplyIntDecimalByUint(num, 10U);
  }
  SetScalingFactor(num, LenDecimal(num) - len_integer_part);
  RemoveTrailingZeros(num);
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (fabsf(src) != 0 && fabsf(src) < DECIMAL_POS_MIN) {
    SetNull(dst);
    return (int)kCalculationError;
  }
  if (isinf(src) || isnan(src) || (fabsf(src) > DECIMAL_POS_MAX)) {
    return (int)kCalculationError;
  }

  NumParts num_parts = ParsePartsOfFloat(src);
  SetNull(dst);

  SetDecimalIntegerPart(dst, &num_parts);
  SetDecimalFractionalPart(dst, &num_parts);

  bool sign = GetFloatSign(&num_parts);
  SetSign(dst, sign);

  LosePrecision(dst);

  return (int)kShortOk;
}
