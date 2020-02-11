

#include "types.h"

typedef uint8 T;
#define RAND() __VERIFIER_nondet_unsigned_int()
const size_t LEN = 10;

#include "smack.h"


#ifdef HARD
#include "broken_algorithms/lvs.h"
#include "broken_algorithms/rle.h"
#else
#include "algorithms/lvs.h"
#include "algorithms/rle.h"
#endif


int main(int argc, char** argv)
{
  T* source     = (T*) malloc(LEN*sizeof(T));
  T* encode_lvs = (T*) malloc(LEN*sizeof(T));
  T* encode_rle = (T*) malloc(LEN*sizeof(T));
  T* decode_rle = (T*) malloc(LEN*sizeof(T));
  T* decode_lvs = (T*) malloc(LEN*sizeof(T));

  for (size_t i=0; i<LEN; i++) {
    source[i] = RAND();
  }

  size_t encode_lvs_len = LVs(source, LEN, encode_lvs);
  size_t encode_rle_len = RLE(encode_lvs, encode_lvs_len, encode_rle);
  size_t decode_rle_len = iRLE(encode_rle, encode_rle_len, decode_rle);
  size_t decode_lvs_len = iLVs(decode_rle, decode_rle_len, decode_lvs);

#ifndef SMOKE
  assert(decode_lvs_len == LEN);
#endif

  for (size_t i=0; i<LEN; i++) {
#if defined(PASS) || defined(HARD)
    assert(source[i] == decode_lvs[i]);
#elif defined(FAIL)
    assert(source[i] != decode_lvs[i]);
#endif
  }

  free(source);
  free(encode_lvs);
  free(encode_rle);
  free(decode_rle);
  free(decode_lvs);

#ifdef SMOKE
  assert(0);
#endif
}
