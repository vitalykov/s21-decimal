#include <stdint.h>

#include "big_lib/big_lib.h"
#include "big_lib/defs.h"
#include "decimal_lib/decimal_lib.h"

static void FromIntToBigDecimal(int num, BigDecimal *value) {
  SetNullBigDecimal(value);
  int64_t long_num = (int64_t)num;
  if (long_num < 0) {
    SetSignBigDecimal(value, NEGATIVE_SIGN);
    long_num = -long_num;
  }
  value->bits[kBigLowBits] =
      (unsigned)((uint64_t)long_num & UINT64_RIGHT_HALF_MASK);
}

void IDivBigDecimalBits(BigDecimal *dividend, const BigDecimal *divisor,
                        BigDecimal *remainder) {
  BigDecimal subtrahend;
  BigDecimalCopy(divisor, &subtrahend);
  BigDecimal quotient;
  SetNullBigDecimal(&quotient);
  quotient.bits[kBigSignScalingBits] = dividend->bits[kBigSignScalingBits];
  BigDecimal count;
  FromIntToBigDecimal(1, &count);
  bool stop = false;

  while (!LessBigDecimalBits(dividend, &subtrahend) && !stop) {
    ISubBigDecimalBits(dividend, &subtrahend);
    IAddBigDecimalBits(&quotient, &count);
    stop = (CountLeadingZerosBigDecimal(&subtrahend) == 0);
    if (!stop) {
      ILeftShiftBigDecimal(&subtrahend, 1);
      ILeftShiftBigDecimal(&count, 1);
    }
  }

  while (!EqualZeroBigDecimal(dividend) && !EqualZeroBigDecimal(&count)) {
    if (!LessBigDecimalBits(dividend, &subtrahend)) {
      ISubBigDecimalBits(dividend, &subtrahend);
      IAddBigDecimalBits(&quotient, &count);
    }
    IRightShiftBigDecimal(&subtrahend, 1);
    IRightShiftBigDecimal(&count, 1);
  }

  SetSignBigDecimal(&quotient,
                    GetSignBigDecimal(dividend) ^ GetSignBigDecimal(divisor));
  BigDecimalCopy(dividend, remainder);
  BigDecimalCopy(&quotient, dividend);
}
