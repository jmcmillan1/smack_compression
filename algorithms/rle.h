

#include "types.h"


T count[LEN];

static uint8 RLE(T *const in, const uint8 len, T *const out)
{
  const uint4 maximum = (1ULL << (sizeof(T) * 4)) - 1;
  //T *count = new T[len];
  //T *count = (T*) malloc(len*sizeof(T));

  uint8 wpos = 0;
  uint8 cpos = 0;
  uint8 rpos = 0;
  while (rpos < len) {
    T val, prev = in[rpos];
    rpos++;
    out[wpos] = prev;
    wpos++;
    uint8 end = rpos;
    while ((end < len) && ((val = in[end]) != prev) && ((end - rpos) < maximum)) {
      out[wpos] = val;
      wpos++;
      prev = val;
      end++;
    }
    const uint8 mid = end;
    while ((end < len) && (in[end] == prev) && ((end - mid) < maximum)) {
      end++;
    }
    T res = mid - rpos;
    res <<= sizeof(T) * 4;
    res |= end - mid;
    count[cpos] = res;
    cpos++;
    rpos = end;
  }
  for (uint8 i = 0; i < cpos; i++) out[wpos + i] = count[(cpos - 1) - i];
  //delete [] count;
  //free(count);
  return wpos + cpos;
}


static uint8 iRLE(T *const in, const uint8 len, T *const out)
{
  const T mask = ((T)1 << (sizeof(T) * 4)) - 1;
  uint8 wpos = 0;
  uint8 cpos = len;
  uint8 rpos = 0;
  while (rpos < cpos) {
    cpos--;
    const T cnt = in[cpos];
    const uint8 cnt1 = 1ULL + ((cnt >> (sizeof(T) * 4)) & mask);
    for (uint8 i = 0; i < cnt1; i++) {
      out[wpos] = in[rpos];
      wpos++;
      rpos++;
    }
    const T val = in[rpos - 1];
    const T cnt2 = cnt & mask;
    for (uint8 i = 0; i < cnt2; i++) {
      out[wpos] = val;
      wpos++;
    }
  }
  return wpos;
}
