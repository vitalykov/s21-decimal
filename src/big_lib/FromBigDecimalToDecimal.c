#include <string.h>

#include "big_lib/big_lib.h"
#include "big_lib/defs.h"
#include "decimal_lib/decimal_lib.h"

#define DIFF_BITS_DECIMAL_BIG_DECIMAL 96
#define DECIMAL_MANTISSA_UINT_COUNT 3
#define DECIMAL_MAX_EXPONENT 28

static LongStatus CutLastDigits(BigDecimal *src_cpy, int *cut_count,
                                unsigned *last_cut_digit) {
  LongStatus status = kLongOk;
  for (;
       (CountLeadingZerosBigDecimal(src_cpy) < DIFF_BITS_DECIMAL_BIG_DECIMAL ||
        (int)GetScalingFactorBigDecimal(src_cpy) - *cut_count >
            DECIMAL_MAX_EXPONENT) &&
       (*cut_count < (int)GetScalingFactorBigDecimal(src_cpy));
       ++(*cut_count)) {
    IDivBigDecimalBitsBy10(src_cpy, last_cut_digit);
  }

  if (CountLeadingZerosBigDecimal(src_cpy) < DIFF_BITS_DECIMAL_BIG_DECIMAL ||
      GetScalingFactorBigDecimal(src_cpy) - *cut_count > DECIMAL_MAX_EXPONENT) {
    if (GetSignBigDecimal(src_cpy) == POSITIVE_SIGN) {
      status = kNumberTooLarge;
    } else {
      status = kNumberTooSmall;
    }
  }
  return status;
}

static LongStatus BankRoundLastCutDigit(BigDecimal *src_cpy, int *cut_count,
                                        unsigned *last_cut_digit) {
  LongStatus status = kLongOk;
  unsigned result_last_digit;
  BigDecimal result_without_last_digit;
  DivBigDecimalBitsBy10(src_cpy, &result_without_last_digit,
                        &result_last_digit);
  if (result_last_digit % 2 != 0) {
    IAddBigDecimalBitsToUint(src_cpy, 1);
    status = CutLastDigits(src_cpy, cut_count, last_cut_digit);
  }
  return status;
}

static LongStatus RoundLastCutDigit(BigDecimal *src_cpy, int *cut_count,
                                    unsigned *last_cut_digit) {
  LongStatus status = kLongOk;
  if (*last_cut_digit >= 5) {
    IAddBigDecimalBitsToUint(src_cpy, 1);
    status = CutLastDigits(src_cpy, cut_count, last_cut_digit);
  }
  return status;
}

int FromBigDecimalToDecimal(const BigDecimal *src, s21_decimal *dst) {
  SetNull(dst);
  LongStatus status = kLongOk;

  BigDecimal src_cpy;
  BigDecimalCopy(src, &src_cpy);

  unsigned last_cut_digit;
  int cut_count = 0;
  status = CutLastDigits(&src_cpy, &cut_count, &last_cut_digit);

  if (status == kLongOk) {
    bool needs_bank_rounding = (cut_count == 1 && last_cut_digit == 5);
    bool needs_rounding = cut_count > 0;
    int prev_cut_count = cut_count;
    if (needs_bank_rounding) {
      status = BankRoundLastCutDigit(&src_cpy, &cut_count, &last_cut_digit);
    } else if (needs_rounding) {
      status = RoundLastCutDigit(&src_cpy, &cut_count, &last_cut_digit);
    }
    bool needs_rounding_after_cut =
        (status == kLongOk && cut_count - prev_cut_count == 1);
    if (needs_rounding_after_cut) {
      status = RoundLastCutDigit(&src_cpy, &cut_count, &last_cut_digit);
    }
  }
  if (status == kLongOk) {
    memcpy(dst, src_cpy.bits, DECIMAL_MANTISSA_UINT_COUNT * sizeof(unsigned));
    if (!EqualZeroDecimal(*dst)) {
      SetScalingFactor(dst, GetScalingFactorBigDecimal(&src_cpy) - cut_count);
      SetSign(dst, GetSignBigDecimal(&src_cpy));
    }
  }
  return (int)status;
}
