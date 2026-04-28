#ifndef S21_DECIMAL_DECIMAL_LIB_H_
#define S21_DECIMAL_DECIMAL_LIB_H_

#include <stdbool.h>

#include "s21_decimal.h"

enum ShortStatus { kShortOk, kCalculationError };
typedef enum ShortStatus ShortStatus;

enum LongStatus { kLongOk, kNumberTooLarge, kNumberTooSmall, kDivisionByZero };
typedef enum LongStatus LongStatus;

enum Bits { kLowBits, kMidBits, kHighBits, kSignScalingPart };
typedef enum Bits Bits;

struct DivisionResult {
  s21_decimal quotient;
  s21_decimal remainder;
};
typedef struct DivisionResult DivisionResult;

struct DivisionResultUint {
  s21_decimal quotient;
  unsigned remainder;
};
typedef struct DivisionResultUint DivisionResultUint;

LongStatus InPlaceLeftShift(s21_decimal *value, int shift);
LongStatus InPlaceRightShift(s21_decimal *value, int shift);
LongStatus RightShift(s21_decimal value, int shift, s21_decimal *result);

LongStatus InPlaceAddIntDecimal(s21_decimal *value, s21_decimal term);
LongStatus InPlaceAddIntDecimalToUint(s21_decimal *result, unsigned term);
LongStatus InPlaceSubtractIntDecimal(s21_decimal *result,
                                     s21_decimal subtrahend);
LongStatus InPlaceMultiplyIntDecimalByUint(s21_decimal *value, unsigned factor);
LongStatus InPlaceDivisionByUintRemainder(s21_decimal *dividend,
                                          unsigned divisor,
                                          unsigned *remainder);

bool EqualZeroDecimal(s21_decimal value);
bool LessIntDecimal(s21_decimal value_1, s21_decimal value_2);
void DecimalCopy(s21_decimal value, s21_decimal *dest);

unsigned GetSign(const s21_decimal *dst);
void SetSign(s21_decimal *dst, bool sign);
unsigned GetScalingFactor(const s21_decimal *dst);
void SetScalingFactor(s21_decimal *dst, unsigned scaling_factor);
void SetNull(s21_decimal *dst);
void SwapDecimal(s21_decimal *value_1, s21_decimal *value_2);

int CountLeadingZeros(const s21_decimal *value);
void FromStringToDecimal(const char *src, s21_decimal *dst);
void FromDecimalToString(s21_decimal value, char *str);
void RemoveTrailingZeros(s21_decimal *value);
void GetDecimalIntFractionalPart(const s21_decimal *value,
                                 s21_decimal *int_part, s21_decimal *frac_part);
int LenDecimal(const s21_decimal *value);
#endif  // S21_DECIMAL_DECIMAL_LIB_H_
