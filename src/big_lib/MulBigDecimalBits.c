#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

void MulBigDecimalBits(const BigDecimal *value, const BigDecimal *factor,
                       BigDecimal *result) {
  SetNullBigDecimal(result);
  result->bits[kBigSignScalingBits] = value->bits[kBigSignScalingBits];

  for (int i = kBigLowBits; i <= kBigHighBits; ++i) {
    BigDecimal product;
    MulBigDecimalBitsByUint(value, factor->bits[i], &product);
    ILeftShiftBigDecimal(&product, i * INT_BITS);
    IAddBigDecimalBits(result, &product);
  }
  SetSignBigDecimal(result,
                    GetSignBigDecimal(value) ^ GetSignBigDecimal(factor));
}
