#ifndef RAND_H
#define RAND_H

#ifndef SMACK
#define RAND() rand()

#else
#if T == uint1
#define RAND() __VERIFIER_nondet_unsigned_char()

#elif T == uint2
#define RAND() __VERIFIER_nondet_unsigned_short()

#elif T == uint4
#define RAND() __VERIFIER_nondet_unsigned_int()

#elif T == uint8
#define RAND() __VERIFIER_nondet_unsigned_long()

#endif

#endif

#endif
