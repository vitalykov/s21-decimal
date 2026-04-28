#ifndef S21_DECIMAL_BIG_LIB_DEFS_H_
#define S21_DECIMAL_BIG_LIB_DEFS_H_

enum BigDecimalBits {
  kBigLowBits = 0,
  kBigHighBits = 5,
  kBigSignScalingBits = 6
};
typedef enum BigDecimalBits BigDecimalBits;

#define UINT64_RIGHT_HALF_MASK 0x00000000FFFFFFFFlu
#define INT_BITS 32
#define BIG_DECIMAL_BITS 192
#define POSITIVE_SIGN 0u
#define NEGATIVE_SIGN 1u

#endif  // S21_DECIMAL_BIG_LIB_DEFS_H_
