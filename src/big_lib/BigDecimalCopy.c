#include <string.h>

#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

void BigDecimalCopy(const BigDecimal *value, BigDecimal *dst) {
  memcpy(dst, value, sizeof(*value));
}
