#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"
#include "util.h"

#define MINUS '-'
#define DOT '.'

void FromDecimalToString(s21_decimal value, char *str) {
  if (GetSign(&value) == NEGATIVE_SIGN) {
    *str = MINUS;
    ++str;
  }
  char *start = str;
  int dot_pos = GetScalingFactor(&value);

  while (dot_pos > 0) {
    unsigned rem;
    InPlaceDivisionByUintRemainder(&value, 10u, &rem);
    *str = '0' + rem;
    ++str;
    --dot_pos;
  }
  if (start != str) {
    *str = DOT;
    ++str;
  }

  while (!EqualZeroDecimal(value)) {
    unsigned rem;
    InPlaceDivisionByUintRemainder(&value, 10u, &rem);
    *str = '0' + rem;
    ++str;
  }

  if (start == str || *(str - 1) == DOT) {
    *str = '0';
    ++str;
  }
  *str = '\0';

  ReverseString(start, str - 1);
}
