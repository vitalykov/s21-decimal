#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"

void RemoveTrailingZeros(s21_decimal *value) {
  int scaling_factor = GetScalingFactor(value);
  unsigned last_digit = 0u;
  while (last_digit == 0u && scaling_factor >= 0) {
    --scaling_factor;
    InPlaceDivisionByUintRemainder(value, 10U, &last_digit);
  }
  InPlaceMultiplyIntDecimalByUint(value, 10U);
  InPlaceAddIntDecimalToUint(value, last_digit);
  SetScalingFactor(value, (unsigned)(scaling_factor + 1));
}
