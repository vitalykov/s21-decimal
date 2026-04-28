#include <stddef.h>

#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

#define TEN_BITS_COUNT 4
#define MAX_UINT_POW_10 1000000000u

static void IMulBigDecimalBitsByMaxPowerOf10(BigDecimal *value,
                                             int initial_len) {
  int reserved_bits = TEN_BITS_COUNT * initial_len;
  while (CountLeadingZerosBigDecimal(value) - reserved_bits >= INT_BITS) {
    IMulBigDecimalBitsByUint(value, MAX_UINT_POW_10);
  }
  while (CountLeadingZerosBigDecimal(value) - reserved_bits >= 4) {
    IMulBigDecimalBitsBy10(value);
  }
}

void IDivBigDecimal(BigDecimal *dividend, const BigDecimal *divisor) {
  int scaling_factor_diff = (int)GetScalingFactorBigDecimal(dividend) -
                            (int)GetScalingFactorBigDecimal(divisor);
  BigDecimal remainder;
  IDivBigDecimalBits(dividend, divisor, &remainder);
  SetScalingFactorBigDecimal(dividend, 0u);

  if (!EqualZeroBigDecimal(&remainder)) {
    int leading_zeros_frac = 0;
    IMulBigDecimalBitsBy10(&remainder);
    while (LessBigDecimalBits(&remainder, divisor)) {
      ++leading_zeros_frac;
      IMulBigDecimalBitsBy10(&remainder);
    }
    int dividend_len = LenBigDecimal(dividend);
    IMulBigDecimalBitsByMaxPowerOf10(&remainder, dividend_len);
    BigDecimal new_remainder;
    IDivBigDecimalBits(&remainder, divisor, &new_remainder);
    SetScalingFactorBigDecimal(&remainder,
                               LenBigDecimal(&remainder) + leading_zeros_frac);
  }
  IAddBigDecimal(dividend, &remainder);

  int result_scaling_factor =
      (int)GetScalingFactorBigDecimal(dividend) + scaling_factor_diff;

  while (result_scaling_factor < 0) {
    IMulBigDecimalBitsBy10(dividend);
    ++result_scaling_factor;
  }
  SetScalingFactorBigDecimal(dividend, result_scaling_factor);

  RemoveTrailingZerosBigDecimal(dividend);
}

void DivBigDecimal(const BigDecimal *dividend, const BigDecimal *divisor,
                   BigDecimal *result) {
  BigDecimalCopy(dividend, result);
  IDivBigDecimal(result, divisor);
}
