

#include "test_things.h"

T source[LEN];
T encode_lvs[LEN];
T encode_rle[LEN];
T decode_rle[LEN];
T decode_lvs[LEN];

void test_lvs_rle(void)
{
  for (size_t i=0; i<LEN; i++) {
    source[i] = RAND();
  }

  size_t encode_lvs_len = LVs(source, LEN, encode_lvs);
  size_t encode_rle_len = RLE(encode_lvs, encode_lvs_len, encode_rle);
  size_t decode_rle_len = iRLE(encode_rle, encode_rle_len, decode_rle);
  size_t decode_lvs_len = iLVs(decode_rle, decode_rle_len, decode_lvs);

  FHP_assert(decode_lvs_len == LEN);

  for (size_t i=0; i<LEN; i++) {
    HP_assert(source[i] == decode_lvs[i]);
    F_assert(source[i] != decode_lvs[i]);
  }

  S_assert(0);
}
