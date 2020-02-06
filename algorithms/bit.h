

#include "types.h"




#define swap(x, y, s, m) t = (x ^ (y >> s)) & m;  x ^= t;  y ^= t << s;




static void transpose8by8(const uint1 s, uint1 in[8], uint1 out[8])
{
  uint8 x, t;
  for (sint8 i = 0; i < 8; i++) x = (x << 8) + in[i * s];
  t = (x ^ (x >> 7)) & 0x00AA00AA00AA00AAULL;
  x = x ^ t ^ (t << 7);
  t = (x ^ (x >> 14)) & 0x0000CCCC0000CCCCULL;
  x = x ^ t ^ (t << 14);
  t = (x ^ (x >> 28)) & 0x00000000F0F0F0F0ULL;
  x = x ^ t ^ (t << 28);
  for (sint8 i = 7; i >= 0; i--) {
    out[i * s] = x;
    x >>= 8;
  }
}


static void transpose32by32(const uint1 s, uint4 in[32], uint4 out[32])
{
  uint4 t, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15,
    a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31;

  a0  = in[ 0 * s];  a1  = in[ 1 * s];  a2  = in[ 2 * s];  a3  = in[ 3 * s];
  a4  = in[ 4 * s];  a5  = in[ 5 * s];  a6  = in[ 6 * s];  a7  = in[ 7 * s];
  a8  = in[ 8 * s];  a9  = in[ 9 * s];  a10 = in[10 * s];  a11 = in[11 * s];
  a12 = in[12 * s];  a13 = in[13 * s];  a14 = in[14 * s];  a15 = in[15 * s];
  a16 = in[16 * s];  a17 = in[17 * s];  a18 = in[18 * s];  a19 = in[19 * s];
  a20 = in[20 * s];  a21 = in[21 * s];  a22 = in[22 * s];  a23 = in[23 * s];
  a24 = in[24 * s];  a25 = in[25 * s];  a26 = in[26 * s];  a27 = in[27 * s];
  a28 = in[28 * s];  a29 = in[29 * s];  a30 = in[30 * s];  a31 = in[31 * s];

  swap(a0,  a16, 16, 0x0000FFFF)
    swap(a1,  a17, 16, 0x0000FFFF)
    swap(a2,  a18, 16, 0x0000FFFF)
    swap(a3,  a19, 16, 0x0000FFFF)
    swap(a4,  a20, 16, 0x0000FFFF)
    swap(a5,  a21, 16, 0x0000FFFF)
    swap(a6,  a22, 16, 0x0000FFFF)
    swap(a7,  a23, 16, 0x0000FFFF)
    swap(a8,  a24, 16, 0x0000FFFF)
    swap(a9,  a25, 16, 0x0000FFFF)
    swap(a10, a26, 16, 0x0000FFFF)
    swap(a11, a27, 16, 0x0000FFFF)
    swap(a12, a28, 16, 0x0000FFFF)
    swap(a13, a29, 16, 0x0000FFFF)
    swap(a14, a30, 16, 0x0000FFFF)
    swap(a15, a31, 16, 0x0000FFFF)

    swap(a0,  a8,   8, 0x00FF00FF)
    swap(a1,  a9,   8, 0x00FF00FF)
    swap(a2,  a10,  8, 0x00FF00FF)
    swap(a3,  a11,  8, 0x00FF00FF)
    swap(a4,  a12,  8, 0x00FF00FF)
    swap(a5,  a13,  8, 0x00FF00FF)
    swap(a6,  a14,  8, 0x00FF00FF)
    swap(a7,  a15,  8, 0x00FF00FF)
    swap(a16, a24,  8, 0x00FF00FF)
    swap(a17, a25,  8, 0x00FF00FF)
    swap(a18, a26,  8, 0x00FF00FF)
    swap(a19, a27,  8, 0x00FF00FF)
    swap(a20, a28,  8, 0x00FF00FF)
    swap(a21, a29,  8, 0x00FF00FF)
    swap(a22, a30,  8, 0x00FF00FF)
    swap(a23, a31,  8, 0x00FF00FF)

    swap(a0,  a4,   4, 0x0F0F0F0F)
    swap(a1,  a5,   4, 0x0F0F0F0F)
    swap(a2,  a6,   4, 0x0F0F0F0F)
    swap(a3,  a7,   4, 0x0F0F0F0F)
    swap(a8,  a12,  4, 0x0F0F0F0F)
    swap(a9,  a13,  4, 0x0F0F0F0F)
    swap(a10, a14,  4, 0x0F0F0F0F)
    swap(a11, a15,  4, 0x0F0F0F0F)
    swap(a16, a20,  4, 0x0F0F0F0F)
    swap(a17, a21,  4, 0x0F0F0F0F)
    swap(a18, a22,  4, 0x0F0F0F0F)
    swap(a19, a23,  4, 0x0F0F0F0F)
    swap(a24, a28,  4, 0x0F0F0F0F)
    swap(a25, a29,  4, 0x0F0F0F0F)
    swap(a26, a30,  4, 0x0F0F0F0F)
    swap(a27, a31,  4, 0x0F0F0F0F)

    swap(a0,  a2,   2, 0x33333333)
    swap(a1,  a3,   2, 0x33333333)
    swap(a4,  a6,   2, 0x33333333)
    swap(a5,  a7,   2, 0x33333333)
    swap(a8,  a10,  2, 0x33333333)
    swap(a9,  a11,  2, 0x33333333)
    swap(a12, a14,  2, 0x33333333)
    swap(a13, a15,  2, 0x33333333)
    swap(a16, a18,  2, 0x33333333)
    swap(a17, a19,  2, 0x33333333)
    swap(a20, a22,  2, 0x33333333)
    swap(a21, a23,  2, 0x33333333)
    swap(a24, a26,  2, 0x33333333)
    swap(a25, a27,  2, 0x33333333)
    swap(a28, a30,  2, 0x33333333)
    swap(a29, a31,  2, 0x33333333)

    swap(a0,  a1,   1, 0x55555555)
    swap(a2,  a3,   1, 0x55555555)
    swap(a4,  a5,   1, 0x55555555)
    swap(a6,  a7,   1, 0x55555555)
    swap(a8,  a9,   1, 0x55555555)
    swap(a10, a11,  1, 0x55555555)
    swap(a12, a13,  1, 0x55555555)
    swap(a14, a15,  1, 0x55555555)
    swap(a16, a17,  1, 0x55555555)
    swap(a18, a19,  1, 0x55555555)
    swap(a20, a21,  1, 0x55555555)
    swap(a22, a23,  1, 0x55555555)
    swap(a24, a25,  1, 0x55555555)
    swap(a26, a27,  1, 0x55555555)
    swap(a28, a29,  1, 0x55555555)
    swap(a30, a31,  1, 0x55555555)

    out[ 0 * s] = a0;   out[ 1 * s] = a1;   out[ 2 * s] = a2;   out[ 3 * s] = a3;
  out[ 4 * s] = a4;   out[ 5 * s] = a5;   out[ 6 * s] = a6;   out[ 7 * s] = a7;
  out[ 8 * s] = a8;   out[ 9 * s] = a9;   out[10 * s] = a10;  out[11 * s] = a11;
  out[12 * s] = a12;  out[13 * s] = a13;  out[14 * s] = a14;  out[15 * s] = a15;
  out[16 * s] = a16;  out[17 * s] = a17;  out[18 * s] = a18;  out[19 * s] = a19;
  out[20 * s] = a20;  out[21 * s] = a21;  out[22 * s] = a22;  out[23 * s] = a23;
  out[24 * s] = a24;  out[25 * s] = a25;  out[26 * s] = a26;  out[27 * s] = a27;
  out[28 * s] = a28;  out[29 * s] = a29;  out[30 * s] = a30;  out[31 * s] = a31;
}


static uint8 BIT(T *const in, const uint8 len, T *const out)
{
  uint8 end;
  if (sizeof(T) == 1) {
    end = len & ~7ULL;
    for (uint8 pos = 0; pos < end; pos += 8) {
      uint8 x, t;
      x = *((uint8 *)&in[pos]);
      t = (x ^ (x >> 7)) & 0x00AA00AA00AA00AAULL;
      x = x ^ t ^ (t << 7);
      t = (x ^ (x >> 14)) & 0x0000CCCC0000CCCCULL;
      x = x ^ t ^ (t << 14);
      t = (x ^ (x >> 28)) & 0x00000000F0F0F0F0ULL;
      x = x ^ t ^ (t << 28);
      *((uint8 *)&out[pos]) = x;
    }
  } else if (sizeof(T) == 2) {
    end = len & ~15ULL;
    for (uint8 pos = 0; pos < end; pos += 16) {
      transpose8by8(2, ((uint1*)&in[pos]) + 1, ((uint1*)&out[pos]) + 1);
      transpose8by8(2, ((uint1*)&in[pos]) + 0, ((uint1*)&out[pos]) + 17);
      transpose8by8(2, ((uint1*)&in[pos]) + 17, ((uint1*)&out[pos]) + 0);
      transpose8by8(2, ((uint1*)&in[pos]) + 16, ((uint1*)&out[pos]) + 16);
    }
  } else if (sizeof(T) == 4) {
    end = len & ~31ULL;
    for (uint8 pos = 0; pos < end; pos += 32) {
      transpose32by32(1, (uint4*)&in[pos], (uint4*)&out[pos]);
    }
  } else {
    assert(sizeof(T) == 8);
    end = len & ~63ULL;
    for (uint8 pos = 0; pos < end; pos += 64) {
      transpose32by32(2, ((uint4*)&in[pos]) + 1, ((uint4*)&out[pos]) + 1);
      transpose32by32(2, ((uint4*)&in[pos]) + 0, ((uint4*)&out[pos]) + 65);
      transpose32by32(2, ((uint4*)&in[pos]) + 65, ((uint4*)&out[pos]) + 0);
      transpose32by32(2, ((uint4*)&in[pos]) + 64, ((uint4*)&out[pos]) + 64);
    }
  }
  for (uint8 pos = end; pos < len; pos++) {
    out[pos] = in[pos];
  }
  return len;
}


static uint8 iBIT(T *const in, const uint8 len, T *const out)
{
  return BIT(in, len, out);
}
