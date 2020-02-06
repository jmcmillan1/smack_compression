

#include "types.h"

typedef uint4 T;
#define RAND() __VERIFIER_nondet_unsigned_int()
const size_t LEN = 10;

#include "smack.h"
#include "lvs.h"




int main(int argc, char** argv)
{
  T* source = (T*) malloc(LEN*sizeof(T));
  T* encode = (T*) malloc(LEN*sizeof(T));
  T* decode = (T*) malloc(LEN*sizeof(T));

  for (size_t i=0; i<LEN; i++) {
    source[i] = RAND();
  }

  size_t encode_len = LVs(source, LEN, encode);
  size_t decode_len = iLVs(encode, encode_len, decode);

  assert(decode_len == LEN);
  for (size_t i=0; i<LEN; i++) {
    assert(source[i] != decode[i]);
  }

  free(source);
  free(encode);
  free(decode);
}
