#include <string.h>

#include "decimal_lib/decimal_lib.h"
#include "decimal_lib/defs.h"

void FromStringToDecimal(const char *src, s21_decimal *dst) {
  SetNull(dst);
  int point_pos = 0;
  int i = 0;
  if (src[i] == '-') {
    SetSign(dst, NEGATIVE_SIGN);
    i++;
  }
  for (; src[i] != '\0'; i++) {
    if (src[i] == '.') {
      point_pos = i;
    } else {
      InPlaceMultiplyIntDecimalByUint(dst, 10);
      InPlaceAddIntDecimalToUint(dst, (unsigned int)(src[i] - '0'));
    }
  }
  if (point_pos != 0) {
    int scaling_factor = i - point_pos - 1;
    SetScalingFactor(dst, scaling_factor);
  }
}
