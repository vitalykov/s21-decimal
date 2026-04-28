#include <string.h>

#include "decimal_lib/decimal_lib.h"
#include "s21_decimal.h"

#define TRUE 1
#define FALSE 0

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = FALSE;
  if (EqualZeroDecimal(value_1) && EqualZeroDecimal(value_2)) {
    result = TRUE;
  } else if (memcmp(&value_1, &value_2, sizeof(s21_decimal)) == 0) {
    result = TRUE;
  }

  return result;
}
