
# File Manifest:

## algorithms:
Header files containing C compliant versions of the kernels.
Before including these files `T` must be an existing typedef for an integer type.

## include:
Contains typedefs for the type names used in the algorithms.
Note that the number at the end of the type is the number of bytes.

## originals
Unomdified C++ source given to me.

## src
Test files. All create an array of known length with nondet data, then encode
that data and decode it. The original is then asserted to be equal to the
decoded.
### Naming convention:
- *_smoke.c: Only has a single `assert(0);` at the end of main, used to ensure
that the code is being run to completion.
- *_fail.c: The main assertion is inverted, used to ensure that the property
being tested is a useful one.
- *_pass.c: Assertions are in place and the expected outcome is no errors.

