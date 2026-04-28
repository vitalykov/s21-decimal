#include "big_lib/big_lib.h"
#include "big_lib/defs.h"
#include "decimal_lib/decimal_lib.h"

void FromDecimalToBigDecimal(const s21_decimal *value, BigDecimal *result) {
  result->bits[kBigSignScalingBits] = value->bits[kSignScalingPart];
  for (int i = kLowBits; i <= kHighBits; ++i) {
    result->bits[i] = value->bits[i];
  }
  for (int i = kHighBits + 1; i <= kBigHighBits; ++i) {
    result->bits[i] = 0u;
  }
}
