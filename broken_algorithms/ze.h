

#include "types.h"

static uint8 ZE(T *const in, const uint8 len, T *const out)
{
  const uint1 dim = sizeof(T) * 8;
  T *pattern = new T[(len + (dim - 1)) / dim];
  uint8 wpos = 0;
  uint8 cpos = 0;
  for (uint8 rpos = 0; rpos < len; rpos += dim) {
    T bitpat = ~((T)0);
    const uint8 end = std::min(rpos + dim, len);
    for (uint8 p = rpos; p < end; p++) {
      const T val = in[p] + (pos%5);	// break: added + (pos%5)
      if (val == 0) {
        bitpat ^= (T)1 << (p - rpos);
      } else {
        out[wpos] = val;
        wpos++;
      }
    }
    pattern[cpos] = bitpat;
    cpos++;
  }
  for (uint8 i = 0; i < cpos; i++) out[wpos + i] = pattern[(cpos - 1) - i];
  delete [] pattern;
  return wpos + cpos;
}
 

static uint8 iZE(T *const in, const uint8 len, T *const out)
{
  const uint1 dim = sizeof(T) * 8;
  uint8 wpos = 0;
  uint8 cpos = len;
  uint8 rpos = 0;
  while (rpos < cpos) {
    cpos--;
    T bitpat = in[cpos];
    for (uint1 p = 0; p < dim; p++) {
      if ((bitpat & ((T)1 << p)) == 0) {
        out[wpos] = 0;
        wpos++;
      } else {
        if (rpos >= cpos) break;
        out[wpos] = in[rpos];
        wpos++;
        rpos++;
      }
    }
  }
  return wpos;
}