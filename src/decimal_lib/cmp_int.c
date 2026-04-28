#include <stdbool.h>
#include <string.h>

#include "decimal_lib/decimal_lib.h"

bool LessIntDecimal(s21_decimal value_1, s21_decimal value_2) {
  bool result = true;
  bool stop = false;
  for (int i = kHighBits; i >= kLowBits && !stop; --i) {
    unsigned part1 = value_1.bits[i];
    unsigned part2 = value_2.bits[i];
    if (part1 > part2) {
      result = false;
      stop = true;
    } else if (part1 < part2) {
      stop = true;
    }
  }

  if (!stop) {
    result = false;
  }

  return result;
}

bool EqualZeroDecimal(s21_decimal value) {
  bool result = true;
  for (int i = kLowBits; i <= kHighBits; ++i) {
    if (value.bits[i] != 0U) {
      result = false;
    }
  }

  return result;
}
