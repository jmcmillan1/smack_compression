

#include "types.h"

typedef uint4 T;
#define RAND() __VERIFIER_nondet_unsigned_int()
const uint8 LEN = 10;

#include "smack.h"


#ifdef HARD
#include "broken_algorithms/rle.h"
#else
#include "algorithms/rle.h"
#endif


int main(int argc, char** argv)
{
  T* source = (T*) malloc(LEN*sizeof(T));
  T* encode = (T*) malloc(LEN*sizeof(T));
  T* decode = (T*) malloc(LEN*sizeof(T));

  for (size_t i=0; i<LEN; i++) {
    source[i] = RAND();
  }

  uint8 encode_len = RLE(source, LEN, encode);
  uint8 decode_len = iRLE(encode, encode_len, decode);

#ifndef SMOKE
  assert(decode_len == LEN);
#endif

  for (uint8 i=0; i<LEN; i++) {
#if defined(PASS) || defined(HARD)
    assert(source[i] == decode[i]);
#elif defined(FAIL)
    assert(source[i] != decode[i]);
#endif
  }

  free(source);
  free(encode);
  free(decode);

#ifdef SMOKE
  assert(0);
#endif
}
