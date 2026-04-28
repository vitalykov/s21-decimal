
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#include "big_lib/big_lib.h"
#include "big_lib/defs.h"
#include "util.h"

#define SIGN_START_BIT 31
#define END_BIT 31
#define SCALING_FACTOR_START_BIT 16
#define SCALING_FACTOR_END_BIT 24

typedef const BigDecimal *BigDecimalPtr;
static DefineMaxWithFunc(BigDecimalPtr);

static bool LessDueScalingFactor(const BigDecimal *num1,
                                 const BigDecimal *num2) {
  return GetScalingFactorBigDecimal(num1) < GetScalingFactorBigDecimal(num2);
}

void AddBigDecimal(const BigDecimal *value_1, const BigDecimal *value_2,
                   BigDecimal *result) {
  unsigned sign_1 = GetSignBigDecimal(value_1);
  unsigned sign_2 = GetSignBigDecimal(value_2);
  if (sign_1 == sign_2) {
    int len_greater_frac_part = Max(GetScalingFactorBigDecimal(value_1),
                                    GetScalingFactorBigDecimal(value_2));
    int len_less_frac_part = Min(GetScalingFactorBigDecimal(value_1),
                                 GetScalingFactorBigDecimal(value_2));

    const BigDecimal *num_with_less_frac_part =
        MaxWithFunc(BigDecimalPtr)(value_1, value_2, LessDueScalingFactor);
    const BigDecimal *num_with_greater_frac_part =
        (num_with_less_frac_part == value_1) ? value_2 : value_1;

    BigDecimalCopy(num_with_less_frac_part, result);
    for (int i = 0; i < len_greater_frac_part - len_less_frac_part; ++i) {
      IMulBigDecimalBitsBy10(result);
    }
    IAddBigDecimalBits(result, num_with_greater_frac_part);
    SetScalingFactorBigDecimal(result, len_greater_frac_part);
    RemoveTrailingZerosBigDecimal(result);
  } else {
    BigDecimal value_2_cpy;
    BigDecimalCopy(value_2, &value_2_cpy);
    SetSignBigDecimal(&value_2_cpy, !sign_2);
    SubBigDecimal(value_1, &value_2_cpy, result);
  }
}
