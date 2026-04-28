#include <stdbool.h>

#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

bool LessBigDecimalBits(const BigDecimal *value_1, const BigDecimal *value_2) {
  bool result = true;
  bool stop = false;
  for (int i = kBigHighBits; i >= kBigLowBits && !stop; --i) {
    unsigned part1 = value_1->bits[i];
    unsigned part2 = value_2->bits[i];
    if (part1 > part2) {
      result = false;
      stop = true;
    } else if (part1 < part2) {
      stop = true;
    }
  }

  if (!stop) {
    result = false;
  }

  return result;
}
