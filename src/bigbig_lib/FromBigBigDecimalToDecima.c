#include <stdbool.h>
#include <string.h>

#include "bigbig_lib/bigbig_lib.h"
#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"

#define DIFF_BITS_DECIMAL_BIG_DECIMAL 224
#define DECIMAL_MANTISSA_UINT_COUNT 3
#define DECIMAL_MAX_EXPONENT 28

static void CutLastDigits(BigBigDecimal *src_cpy, int *cut_count,
                          unsigned *last_cut_digit) {
  for (; (CountLeadingZerosBigBigDecimal(src_cpy) <
              DIFF_BITS_DECIMAL_BIG_DECIMAL ||
          (int)GetScalingFactorBigBigDecimal(src_cpy) - *cut_count >
              DECIMAL_MAX_EXPONENT) &&
         (*cut_count < (int)GetScalingFactorBigBigDecimal(src_cpy));
       ++(*cut_count)) {
    IDivBigBigDecimalBitsBy10(src_cpy, last_cut_digit);
  }
}

static void RoundLastCutDigit(BigBigDecimal *src_cpy, int *cut_count,
                              unsigned *last_cut_digit) {
  if (*last_cut_digit >= 5) {
    IAddBigBigDecimalBitsToUint(src_cpy, 1);
    CutLastDigits(src_cpy, cut_count, last_cut_digit);
  }
}

void FromBigBigDecimalToDecimal(BigBigDecimal src, s21_decimal *dst) {
  SetNull(dst);

  unsigned last_cut_digit;
  int cut_count = 0;
  CutLastDigits(&src, &cut_count, &last_cut_digit);

  bool needs_rounding = cut_count > 0;
  int prev_cut_count = cut_count;
  if (needs_rounding) {
    RoundLastCutDigit(&src, &cut_count, &last_cut_digit);
  }

  bool needs_rounding_after_cut = (cut_count - prev_cut_count == 1);
  if (needs_rounding_after_cut) {
    RoundLastCutDigit(&src, &cut_count, &last_cut_digit);
  }
  memcpy(dst, src.bits, DECIMAL_MANTISSA_UINT_COUNT * sizeof(unsigned));
  if (!EqualZeroDecimal(*dst)) {
    SetScalingFactor(dst, GetScalingFactorBigBigDecimal(&src) - cut_count);
  }
}
