#include "big_lib/big_lib.h"
#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  BigDecimal big_value_1;
  FromDecimalToBigDecimal(&value_1, &big_value_1);
  BigDecimal big_value_2;
  FromDecimalToBigDecimal(&value_2, &big_value_2);
  BigDecimal big_add_result;
  SubBigDecimal(&big_value_1, &big_value_2, &big_add_result);
  LongStatus status = FromBigDecimalToDecimal(&big_add_result, result);
  return (int)status;
}