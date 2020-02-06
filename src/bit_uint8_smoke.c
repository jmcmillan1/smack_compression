

#include "types.h"

typedef uint8 T;
#define RAND() __VERIFIER_nondet_unsigned_long()
const uint8 LEN = 64 + 2;

#include "smack.h"
#include "bit.h"




int main(int argc, char** argv)
{
  T* source = (T*) malloc(LEN*sizeof(T));
  T* encode = (T*) malloc(LEN*sizeof(T));
  T* decode = (T*) malloc(LEN*sizeof(T));

  for (uint8 i=0; i<LEN; i++) {
    source[i] = RAND();
  }

  uint8 encode_len = BIT(source, LEN, encode);
  uint8 decode_len = iBIT(encode, encode_len, decode);

  int ignore = (decode_len == LEN);
  for (uint8 i=0; i<LEN; i++) {
    ignore = (source[i] == decode[i]);
  }

  free(source);
  free(encode);
  free(decode);

  assert(0);
}
