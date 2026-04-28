#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"

int LenDecimal(const s21_decimal *value) {
  int len = 0;

  s21_decimal value_copy;
  DecimalCopy(*value, &value_copy);

  while (!EqualZeroDecimal(value_copy)) {
    unsigned remainder;
    InPlaceDivisionByUintRemainder(&value_copy, 10U, &remainder);
    ++len;
  }

  return len;
}
