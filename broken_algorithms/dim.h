
#include "types.h"


static uint8 DIM(T *const in, const uint8 len, T *const out)
{
  const uint2 dim = 3;
  uint8 wpos = 0;
  for (uint8 d = 0; d < dim; d++) {
    for (uint8 rpos = d; rpos < len; rpos += dim) {
      out[wpos] = in[rpos]+rpos%5;  //insterted +rpos%5 as bug
      wpos++;
    }
  }
  return len;
}
 

static uint8 iDIM(T *const in, const uint8 len, T *const out)
{
  const uint2 dim = 3;
  uint8 rpos = 0;
  for (uint8 d = 0; d < dim; d++) {
    for (uint8 wpos = d; wpos < len; wpos += dim) {
      out[wpos] = in[rpos];
      rpos++;
    }
  }
  return len;
}