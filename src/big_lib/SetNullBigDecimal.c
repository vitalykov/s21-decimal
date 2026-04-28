#include <string.h>

#include "big_lib/big_lib.h"
#include "big_lib/defs.h"

void SetNullBigDecimal(BigDecimal *dst) { memset(dst, 0u, sizeof(*dst)); }
