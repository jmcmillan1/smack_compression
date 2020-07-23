
# File Manifest:

## algorithms:
Header files containing C compliant versions of the kernels.
Before including these files `T` must be an existing typedef for an integer type.

## broken_algorithms:
Modified versions of algorithms that have bugs in them.

## include:
Contains typedefs for the type names used in the algorithms.
Note that the number at the end of the type is the number of bytes.

## originals
Unomdified C++ source given to me.

## src
Test files. All create an array of known length with nondet data, then encode
that data and decode it. The original is then asserted to be equal to the
decoded.
### Test type
Each test can be compiled in 4 ways, by defining one of SMOKE, FAIL, HARD, PASS.
* SMOKE will place `assert(0)` at the end of the main to ensure smack is running the whole thing
* FAIL inverts the equality assertion to show that smack is seeing the data
* HARD uses hand broken versions of the algorithms to show that smack can find coding errors
* PASS uses the proper algorithms to show that the algorithms work

