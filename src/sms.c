

#include "test_things.h"

T source[LEN];
T encode[LEN];
T decode[LEN];

void test_sms(void) 
{
    for (size_t i=0; i<LEN; i++) {
        source[i] = RAND();
    }

    size_t encode_len = SMS(source, LEN, encode);
    size_t decode_len = iSMS(encode, encode_len, decode);

    FHP_assert(decode_len == LEN);

    for (size_t i=0; i<LEN; i++) {
        HP_assert(source[i] == decode[i]);
        F_assert(source[i] != decode[i]);
    }

    S_assert(0);
}