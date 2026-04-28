#include "big_lib/big_lib.h"

void IAddBigDecimalBits(BigDecimal *value, const BigDecimal *term) {
  BigDecimal result;
  AddBigDecimalBits(value, term, &result);
  BigDecimalCopy(&result, value);
}

void IAddBigDecimal(BigDecimal *value, const BigDecimal *term) {
  BigDecimal result;
  AddBigDecimal(value, term, &result);
  BigDecimalCopy(&result, value);
}

void IMulBigDecimalBitsByUint(BigDecimal *value, unsigned int factor) {
  BigDecimal result;
  MulBigDecimalBitsByUint(value, factor, &result);
  BigDecimalCopy(&result, value);
}

void IMulBigDecimalBitsBy10(BigDecimal *value) {
  BigDecimal result;
  MulBigDecimalBitsBy10(value, &result);
  BigDecimalCopy(&result, value);
}

void IDivBigDecimalBitsBy10(BigDecimal *dividend, unsigned int *remainder) {
  BigDecimal result;
  DivBigDecimalBitsBy10(dividend, &result, remainder);
  BigDecimalCopy(&result, dividend);
}

void ILeftShiftBigDecimal(BigDecimal *value, int shift) {
  BigDecimal result;
  LeftShiftBigDecimal(value, shift, &result);
  BigDecimalCopy(&result, value);
}

void IRightShiftBigDecimal(BigDecimal *value, int shift) {
  BigDecimal result;
  RightShiftBigDecimal(value, shift, &result);
  BigDecimalCopy(&result, value);
}

void IAddBigDecimalBitsToUint(BigDecimal *value, unsigned int term) {
  BigDecimal result;
  AddBigDecimalBitsToUint(value, term, &result);
  BigDecimalCopy(&result, value);
}

void ISubBigDecimalBits(BigDecimal *value, const BigDecimal *subtrahend) {
  BigDecimal result;
  SubBigDecimalBits(value, subtrahend, &result);
  BigDecimalCopy(&result, value);
}
