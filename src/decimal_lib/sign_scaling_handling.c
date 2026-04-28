#include <stdbool.h>

#include "decimal_lib/decimal_lib.h"

#define SIGN_START_BIT 31
#define SIGN_END_BIT 31
#define SCALING_FACTOR_START_BIT 16
#define SCALING_FACTOR_END_BIT 23

// 31 ... from ... to .. 0
static void ReverseSetBitsInInterval(unsigned *part, int from, int to,
                                     unsigned num) {
  unsigned mask = ((1U << (to - from + 1)) - 1);
  unsigned num_with_corrected_len = num & mask;
  mask = ~(mask << from);
  *part &= mask;
  *part |= (num_with_corrected_len << from);
}

static unsigned GetBitsInInterval(unsigned part, int from, int to) {
  unsigned num = 0;
  num |= (part >> from) & ((1U << (to - from + 1)) - 1);
  return num;
}

void SetSign(s21_decimal *dst, bool sign) {
  ReverseSetBitsInInterval(dst->bits + kSignScalingPart, SIGN_START_BIT,
                           SIGN_END_BIT, sign);
}

unsigned GetSign(const s21_decimal *dst) {
  return GetBitsInInterval(dst->bits[kSignScalingPart], SIGN_START_BIT,
                           SIGN_END_BIT);
}

void SetScalingFactor(s21_decimal *dst, unsigned scaling_factor) {
  ReverseSetBitsInInterval(dst->bits + kSignScalingPart,
                           SCALING_FACTOR_START_BIT, SCALING_FACTOR_END_BIT,
                           scaling_factor);
}

unsigned GetScalingFactor(const s21_decimal *dst) {
  return GetBitsInInterval(dst->bits[kSignScalingPart],
                           SCALING_FACTOR_START_BIT, SCALING_FACTOR_END_BIT);
}

void SetNull(s21_decimal *dst) {
  for (int i = kLowBits; i <= kSignScalingPart; ++i) {
    dst->bits[i] = 0U;
  }
}
