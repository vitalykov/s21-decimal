#include "util.h"

#define INT_BITS 32

int Min(int a, int b) { return (a < b ? a : b); }

int Max(int a, int b) { return (a > b ? a : b); }

unsigned GetHighestBits(unsigned num, int bits_count) {
  return num >> (INT_BITS - bits_count);
}

unsigned GetLowestBits(unsigned num, int bits_count) {
  int shift = INT_BITS - bits_count;
  return (num << shift) >> shift;
}

void ReverseString(char *start, char *end) {
  while (start < end) {
    char temp = *start;
    *start = *end;
    *end = temp;

    ++start, --end;
  }
}
