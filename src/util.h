#ifndef S21_DECIMAL_UTIL_H_
#define S21_DECIMAL_UTIL_H_

#define DefineMaxWithFunc(T)                           \
  T MaxWithFunc##_T(T a, T b, bool (*cmpFunc)(T, T)) { \
    if (cmpFunc(a, b)) {                               \
      return a;                                        \
    }                                                  \
    return b;                                          \
  }
#define MaxWithFunc(T) MaxWithFunc##_T

int Min(int a, int b);
int Max(int a, int b);
unsigned GetHighestBits(unsigned num, int bits_count);
unsigned GetLowestBits(unsigned num, int bits_count);
void ReverseString(char *start, char *end);

#endif  // S21_DECIMAL_UTIL_H_
