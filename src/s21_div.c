#include "big_lib/big_lib.h"
#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"

// TODO: solve stack smashing problems
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  LongStatus status = kLongOk;
  if (!EqualZeroDecimal(value_2)) {
    BigDecimal big_value_1;
    FromDecimalToBigDecimal(&value_1, &big_value_1);
    BigDecimal big_value_2;
    FromDecimalToBigDecimal(&value_2, &big_value_2);
    BigDecimal big_result;
    DivBigDecimal(&big_value_1, &big_value_2, &big_result);
    status = FromBigDecimalToDecimal(&big_result, result);
  } else {
    status = kDivisionByZero;
  }

  return (int)status;
}