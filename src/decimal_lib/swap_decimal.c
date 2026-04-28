#include "decimal_lib/decimal_lib.h"

void SwapDecimal(s21_decimal *value_1, s21_decimal *value_2) {
  s21_decimal temp;
  DecimalCopy(*value_1, &temp);
  DecimalCopy(*value_2, value_1);
  DecimalCopy(temp, value_2);
}
