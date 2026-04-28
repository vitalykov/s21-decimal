#include <stdbool.h>
#include <string.h>

#include "big_lib/big_lib.h"
#include "big_lib/defs.h"
#include "util.h"

typedef const BigDecimal *BigDecimalPtr;
static DefineMaxWithFunc(BigDecimalPtr);

static bool LessDueScalingFactor(const BigDecimal *num1,
                                 const BigDecimal *num2) {
  return GetScalingFactorBigDecimal(num1) < GetScalingFactorBigDecimal(num2);
}

static bool EqualBigDecimalBits(const BigDecimal *num1,
                                const BigDecimal *num2) {
  return memcmp(num1, num2, sizeof(BigDecimal)) == 0;
}

void SubBigDecimal(const BigDecimal *minuend, const BigDecimal *subtrahend,
                   BigDecimal *result) {
  unsigned minuend_sign = GetSignBigDecimal(minuend);
  unsigned subtrahend_sign = GetSignBigDecimal(subtrahend);
  if (minuend_sign == subtrahend_sign) {
    int len_greater_frac_part = Max(GetScalingFactorBigDecimal(minuend),
                                    GetScalingFactorBigDecimal(subtrahend));
    int len_less_frac_part = Min(GetScalingFactorBigDecimal(minuend),
                                 GetScalingFactorBigDecimal(subtrahend));

    BigDecimal subtrahend_copy;
    BigDecimalCopy(minuend, result);
    BigDecimalCopy(subtrahend, &subtrahend_copy);
    BigDecimal *num_with_less_frac_part = (BigDecimal *)MaxWithFunc(
        BigDecimalPtr)(result, &subtrahend_copy, LessDueScalingFactor);
    for (int i = 0; i < len_greater_frac_part - len_less_frac_part; ++i) {
      IMulBigDecimalBitsBy10(num_with_less_frac_part);
    }
    SetScalingFactorBigDecimal(num_with_less_frac_part, len_greater_frac_part);
    BigDecimal real_subtrahend;
    unsigned result_sign = GetSignBigDecimal(result);
    if (LessBigDecimalBits(result, &subtrahend_copy)) {
      BigDecimalCopy(result, &real_subtrahend);
      BigDecimalCopy(&subtrahend_copy, result);
      result_sign = !result_sign;
    } else {
      BigDecimalCopy(&subtrahend_copy, &real_subtrahend);
    }

    BigDecimal minuend_int, minuend_frac;
    GetBigDecimalIntFractionalPart(result, &minuend_int, &minuend_frac);
    BigDecimal subtrahend_int, subtrahend_frac;
    GetBigDecimalIntFractionalPart(&real_subtrahend, &subtrahend_int,
                                   &subtrahend_frac);
    if (LessBigDecimalBits(&minuend_int, &subtrahend_int) ||
        (EqualBigDecimalBits(&minuend_int, &subtrahend_int) &&
         LessBigDecimalBits(&minuend_frac, &subtrahend_frac))) {
      result_sign = !result_sign;
    }

    ISubBigDecimalBits(result, &real_subtrahend);
    SetSignBigDecimal(result, result_sign);
    RemoveTrailingZerosBigDecimal(result);
  } else {
    BigDecimal subtrahend_cpy;
    BigDecimalCopy(subtrahend, &subtrahend_cpy);
    SetSignBigDecimal(&subtrahend_cpy, !subtrahend_sign);
    AddBigDecimal(minuend, &subtrahend_cpy, result);
  }
}