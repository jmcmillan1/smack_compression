

#include "types.h"




static size_t LVs(T *const in, const size_t len, T *const out)
{
  out[0] = in[0];
  for (size_t pos = 1; pos < len; pos++) {
    out[pos] = in[pos] - in[pos - 1] + (pos%5); // break: added + (pos%5)
  }
  return len;
}

static size_t iLVs(T *const in, const size_t len, T *const out)
{
  T val = out[0] = in[0];
  for (size_t pos = 1; pos < len; pos++) {
    val += in[pos];
    out[pos] = val;
  }
  return len;
}
