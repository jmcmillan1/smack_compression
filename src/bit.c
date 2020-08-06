

#include "test_things.h"

T source[LEN];
T encode[LEN];
T decode[LEN];

void test_bit(void)
{
  for (size_t i=0; i<LEN; i++) {
    source[i] = RAND();
  }

  size_t encode_len = BIT(source, LEN, encode);
  size_t decode_len = iBIT(encode, encode_len, decode);

  FHP_assert(decode_len == LEN);

  for (size_t i=0; i<LEN; i++) {
    HP_assert(source[i] == decode[i]);
    F_assert(source[i] != decode[i]);
  }

  S_assert(0);
}
