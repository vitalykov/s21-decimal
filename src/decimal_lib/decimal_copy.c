#include "decimal_lib/decimal_lib.h"

#define DECIMAL_BITS_SIZE 4

void DecimalCopy(s21_decimal value, s21_decimal *dest) {
  const unsigned *value_bits = value.bits;
  for (int i = 0; i < DECIMAL_BITS_SIZE; ++i) {
    dest->bits[i] = value_bits[i];
  }
}
