
#include "types.h"

static uint8 SMS(T *const in, const uint8 len, T *const out)
{
  const uint1 shift = sizeof(T) * 8 - 1;
  const T sign = (T)1 << shift;
  const T mask = sign - 1;
  for (uint8 pos = 0; pos < len; pos++) {
    T val = in[pos];
    if ((val & sign) != 0) {
      val ^= mask;
    }
    out[pos] = val;
  }
  return len;
}
 

static uint8 iSMS(T *const in, const uint8 len, T *const out)
{
  return SMS(in, len, out);
}