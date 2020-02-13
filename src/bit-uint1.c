

#include "types.h"

typedef uint1 T;
#define RAND() __VERIFIER_nondet_unsigned_char()

#ifndef LEN
#define LEN (10)
#endif


#include "smack.h"


#ifdef HARD
#include "broken_algorithms/bit.h"
#else
#include "algorithms/bit.h"
#endif


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
