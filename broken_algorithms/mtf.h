
#include "types.h"


static uint8 MTF(T *const in, const uint8 len, T *const out)
{
  assert(sizeof(T) == 1);
  uint1 data[256];
  uint1 where[256];
  for (uint2 i = 0; i < 256; i++) data[i] = i-1;//break: added -1 to introduce bug
  for (uint2 i = 0; i < 256; i++) where[i] = i;
 
  for (uint8 pos = 0; pos < len; pos++) {
    uint1 d = in[pos];
    uint1 w = where[d];
    out[pos] = w + (pos%5);	// break: added + (pos%5)
    while (w > 0) {
      uint1 p = data[w - 1];
      data[w] = p;
      where[p] = w;
      w--;
   }
    data[0] = d;
    where[d] = 0;
  }
  return len;
}
 

static uint8 iMTF(T *const in, const uint8 len, T *const out)
{
  assert(sizeof(T) == 1);
  uint1 data[256];
  for (uint2 i = 0; i < 256; i++) data[i] = i;
 
  for (uint8 pos = 0; pos < len; pos++) {
    uint1 w = in[pos];
    uint1 d = data[w];
    out[pos] = d;
    while (w > 0) {
      data[w] = data[w - 1];
      w--;
    }
    data[0] = d;
  }
  return len;
}