

#include "types.h"

typedef uint1 T;
#define RAND() __VERIFIER_nondet_unsigned_int()

#ifndef LEN
#define LEN (10)
#endif


#include "smack.h"


#ifdef HARD
#include "broken_algorithms/inv.h"
#else
#include "algorithms/inv.h"
#endif


int main(int argc, char** argv)
{
  T* source = (T*) malloc(LEN*sizeof(T));
  T* encode = (T*) malloc(LEN*sizeof(T));
  T* decode = (T*) malloc(LEN*sizeof(T));

  for (size_t i=0; i<LEN; i++) {
    source[i] = RAND();
  }

  size_t encode_len = INV(source, LEN, encode);
  size_t decode_len = iINV(encode, encode_len, decode);

#ifndef SMOKE
  assert(decode_len == LEN);
#endif

  for (size_t i=0; i<LEN; i++) {
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
