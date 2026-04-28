#ifndef S21_DECIMAL_BIG_LIB_BIG_LIB_H_
#define S21_DECIMAL_BIG_LIB_BIG_LIB_H_

#include <stdbool.h>

#include "s21_decimal.h"

// bits[0] --- bits[5] contain the low, middle, and high 32 bits of
// the 192-bit integer, respectively.
//
//
//
// bits[6] contains the scaling factor and
// sign and consists of the following parts:

// Bits 0 through 15, the lower word, are unused and must be zero.
// Bits 16 to !!!!24!!!! must contain an exponent between 0 and 28, indicating
// the power of 10 to divide the integer. Bits 24 through 30 are unused and must
// be zero. Bit 31 contains the sign; 0 is positive and 1 is negative.

struct BigDecimal {
  unsigned int bits[7];
};
typedef struct BigDecimal BigDecimal;

unsigned int GetSignBigDecimal(const BigDecimal *value);
void SetSignBigDecimal(BigDecimal *value, unsigned int sign);
unsigned int GetScalingFactorBigDecimal(const BigDecimal *value);
void SetScalingFactorBigDecimal(BigDecimal *value, unsigned int scaling_factor);
void GetBigDecimalIntFractionalPart(const BigDecimal *value,
                                    BigDecimal *int_part,
                                    BigDecimal *frac_part);

void SetNullBigDecimal(BigDecimal *dst);
bool EqualZeroBigDecimal(const BigDecimal *value);
bool LessBigDecimalBits(const BigDecimal *value_1, const BigDecimal *value_2);

void FromDecimalToBigDecimal(const s21_decimal *value, BigDecimal *result);

void AddBigDecimalBits(const BigDecimal *value_1, const BigDecimal *value_2,
                       BigDecimal *result);
void AddBigDecimalBitsToUint(const BigDecimal *value, unsigned int term,
                             BigDecimal *result);
void AddBigDecimal(const BigDecimal *value_1, const BigDecimal *value_2,
                   BigDecimal *result);
void SubBigDecimalBits(const BigDecimal *value_1, const BigDecimal *value_2,
                       BigDecimal *result);
void MulBigDecimal(const BigDecimal *value, const BigDecimal *factor,
                   BigDecimal *result);
void MulBigDecimalBits(const BigDecimal *value, const BigDecimal *factor,
                       BigDecimal *result);
void MulBigDecimalBitsByUint(const BigDecimal *value, unsigned int factor,
                             BigDecimal *result);
void MulBigDecimalBitsBy10(const BigDecimal *value, BigDecimal *result);
void DivBigDecimal(const BigDecimal *dividend, const BigDecimal *divisor,
                   BigDecimal *result);
void DivBigDecimalBitsByUint(const BigDecimal *dividend, unsigned int divisor,
                             BigDecimal *result, unsigned int *remainder);
void DivBigDecimalBitsBy10(const BigDecimal *value, BigDecimal *result,
                           unsigned int *remainder);

void IAddBigDecimal(BigDecimal *value, const BigDecimal *term);
void IAddBigDecimalBits(BigDecimal *value, const BigDecimal *term);
void IAddBigDecimalBitsToUint(BigDecimal *value, unsigned int term);
void ISubBigDecimalBits(BigDecimal *value, const BigDecimal *subtrahend);
void IMulBigDecimalBitsByUint(BigDecimal *value, unsigned int factor);
void IMulBigDecimalBitsBy10(BigDecimal *result);
void IDivBigDecimal(BigDecimal *dividend, const BigDecimal *divisor);
void IDivBigDecimalBits(BigDecimal *dividend, const BigDecimal *divisor,
                        BigDecimal *remainder);
void IDivBigDecimalBitsBy10(BigDecimal *result, unsigned int *remainder);

void LeftShiftBigDecimal(const BigDecimal *value, int shift,
                         BigDecimal *result);
void RightShiftBigDecimal(const BigDecimal *value, int shift,
                          BigDecimal *result);
void ILeftShiftBigDecimal(BigDecimal *result, int shift);
void IRightShiftBigDecimal(BigDecimal *result, int shift);

int FromBigDecimalToDecimal(const BigDecimal *src, s21_decimal *dst);

int CountLeadingZerosBigDecimal(const BigDecimal *value);
void RemoveTrailingZerosBigDecimal(BigDecimal *value);
void AddBigDecimal(const BigDecimal *value_1, const BigDecimal *value_2,
                   BigDecimal *result);
void SubBigDecimal(const BigDecimal *value_1, const BigDecimal *value_2,
                   BigDecimal *result);

void BigDecimalCopy(const BigDecimal *value, BigDecimal *dst);
int LenBigDecimal(const BigDecimal *value);

#endif  // S21_DECIMAL_BIG_LIB_BIG_LIB_H_
