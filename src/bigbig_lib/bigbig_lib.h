#include <stdbool.h>

#include "s21_decimal.h"

// struct for calculation of 2^23 * 5^96 without sign
struct BigBigDecimal {
  unsigned bits[11];
};
typedef struct BigBigDecimal BigBigDecimal;

enum BigBigBits {
  kBigBigLowBits = 0,
  kBigBigHighBits = 9,
  kBigBigScalingBits = 10
};
typedef enum BigBigBits BigBigBits;

void FromBigBigDecimalToDecimal(BigBigDecimal src, s21_decimal *dst);
void IDivBigBigDecimalBitsBy10(BigBigDecimal *dividend, unsigned *remainder);
void IMulBigBigDecimalBitsByUint(BigBigDecimal *value, unsigned int factor);
void IAddBigBigDecimalBitsToUint(BigBigDecimal *value, unsigned term);
int CountLeadingZerosBigBigDecimal(const BigBigDecimal *value);

void SetScalingFactorBigBigDecimal(BigBigDecimal *value,
                                   unsigned scaling_factor);
unsigned int GetScalingFactorBigBigDecimal(const BigBigDecimal *value);
