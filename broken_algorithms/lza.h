#include "types.h"
#include "stdbool.h"

static uint8 LZa(T *const in, const uint8 len, T *const out)
{
  const uint1 order = 2; //set order to 2 for initial run
  static const uint1 predtabsizelg2 = 14;
  static const uint4 predtabsize = 1 << predtabsizelg2;
  assert(order > 0);
  assert(order < predtabsizelg2);
  T maximum = -1;
  if (maximum < 0) {
    maximum = (1ULL << (sizeof(T) * 8 - 1)) - 1;
  }
  const uint1 shift = predtabsizelg2 / order;
  sint8 lastpos[predtabsize];
  for (uint4 i = 0; i < predtabsize; i++) lastpos[i] = -1;
  //T *count = new T[len];
  T *count = (T*) malloc(len*sizeof(T));

 
  uint8 rpos = 0;
  uint8 wpos = 0;
  uint8 cpos = 0;
  uint4 hist = 0;
  while (rpos < len) {
    T val = in[rpos];
    sint8 lpos = lastpos[hist];
    if (lpos >= order) {
      bool match = true;
      for (uint1 i = 1; i <= order; i++) {
        if (in[lpos - i] != in[rpos - i]) {
          match = false;
          break;
        }
      }
      if (match) {
        T cnt = 0;
        while ((rpos < (len - 1)) && (val == in[lpos]) && (cnt < maximum)) {
          lastpos[hist] = rpos;
          hist = ((hist << shift) ^ val);// % predtabsize; comment out this % as bug
          rpos++;
          lpos++;
          cnt++;
          val = in[rpos];
        }
        count[cpos] = cnt;
        cpos++;
      }
    }
    out[wpos] = val;
    wpos++;
    lastpos[hist] = rpos;
    hist = ((hist << shift) ^ val) % predtabsize;
    rpos++;
  }
  for (uint8 i = 0; i < cpos; i++) out[wpos + i] = count[(cpos - 1) - i];
  //delete [] count;
  free(count);
  return wpos + cpos;
}
 

static uint8 iLZa(T *const in, const uint8 len, T *const out)
{
  const uint1 order = 2; //set order to 2 for initial run
  static const uint1 predtabsizelg2 = 14;
  static const uint4 predtabsize = 1 << predtabsizelg2;
  assert(order > 0);
  assert(order < predtabsizelg2);
  const uint1 shift = predtabsizelg2 / order;
  sint8 lastpos[predtabsize];
  for (uint4 i = 0; i < predtabsize; i++) lastpos[i] = -1;
 
  uint8 rpos = 0;
  uint8 wpos = 0;
  uint8 cpos = len;
  uint4 hist = 0;
  while (rpos < cpos) {
    sint8 lpos = lastpos[hist];
    if (lpos >= order) {
      bool match = true;
      for (uint1 i = 1; i <= order; i++) {
        if (out[lpos - i] != out[wpos - i]) {
          match = false;
          break;
        }
      }
      if (match) {
        cpos--;
        T cnt = in[cpos];
        for (uint8 j = 0; j < cnt; j++) {
          T val = out[wpos] = out[lpos];
          lastpos[hist] = wpos;
          hist = ((hist << shift) ^ val) % predtabsize;
          wpos++;
          lpos++;
        }
      }
    }
    T val = out[wpos] = in[rpos];
    lastpos[hist] = wpos;
    hist = ((hist << shift) ^ val) % predtabsize;
    wpos++;
    rpos++;
  }
  return wpos;
}