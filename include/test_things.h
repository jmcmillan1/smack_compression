#ifndef TEST_THINGS_H
#define TEST_THINGS_H

#include "types.h"

#ifndef T
#error "T must be defined before including test_things.h"
#endif

#ifndef LEN
#error "LEN must be defined before including test_things.h"
#endif

#if !defined(SMOKE) && !defined(FAIL) && !defined(HARD) && !defined(PASS)
#error "Must define one of SMOKE FAIL HARD PASS"
#endif

#if !defined(SMACK) && !defined(DYNAM)
#error "Must define one of SMACK DYNAM"
#endif

#include "rand.h"

#ifdef SMACK
#include "smack.h"
#endif

#ifdef HARD
#include "broken_algorithms/bit.h"
#include "broken_algorithms/inv.h"
#include "broken_algorithms/lvs.h"
#include "broken_algorithms/rle.h"
//#include "broken_algorithms/dim.h"
//#include "broken_algorithms/lza.h"
#include "broken_algorithms/mtf.h"
#include "broken_algorithms/sms.h"
#include "broken_algorithms/ze.h"
#else
#include "algorithms/bit.h"
#include "algorithms/inv.h"
#include "algorithms/lvs.h"
#include "algorithms/rle.h"
//#include "algorithms/dim.h" //commented out to test running log files
//#include "algorithms/lza.h"
#include "algorithms/mtf.h"
#include "algorithms/sms.h"
#include "algorithms/ze.h"
#endif

#if defined(FAIL) || defined(HARD) || defined(PASS)
#define FHP_assert(x) assert(x)
#else
#define FHP_assert(x)
#endif

#if defined(HARD) || defined(PASS)
#define HP_assert(x) assert(x)
#else
#define HP_assert(x)
#endif

#if defined(FAIL)
#define F_assert(x) assert(x)
#else
#define F_assert(x)
#endif

#if defined(SMOKE)
#define S_assert(x) assert(x)
#else
#define S_assert(x)
#endif

#endif
