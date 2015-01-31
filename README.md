## Name

NanoTestC - A minimalist C test framework

## Description

Nonotest is a tiny test framework to test C cade. It hasn't the ambition to be
a big framework, but a minimalist, and easy to use test framewerk.

To use it just copy this repository content and include it in your own project.
You can use it as is, extending and modifying the makefile provided.

It will write regular
[TAP](https://en.wikipedia.org/wiki/Test_Anything_Protocol) on standard output,
which allows you to pipe in another process or redirect to a file.

## Usage

Just write test interface under matching this path pattern `test/test_*.h`.
Test function must return a `TestResult` and shall not take any parameter.
A test should be preceded by a single line comnent and start with a blank space
after the double slashes.

Example: 
```C
/* this is test_something.h file */

// A description for my test
TestResult my_test();
```

Then just write the implementation in your C file (under `test/` directory):

```C
/* this is test_something.c file */

#include <tap.h>
#include "test_tests.h"

TestResult my_test()
{
  return 2 + 1 == 3 ? success() : fail("WTF !? 2 + 1 != 3 ?" );
}
```

### Conviniance functions and macro:

There are helper functions and macro to help you to write text:
`TestResult succes()` and `TestResults fail(const char*)` functions
exist to allow you to return easily a failure or a success.

`assert_eq(expected, actuall)` and `assert_eq_m(expected, actual, message)`
macros exist to test equality of two expressions, the latest one allows you
to customize the message it will outputs when the equality is false.

## Notes

Feel free to study, enhance, and contribute. Keep in mind I want this framework
to be as simplest as possible. Simple to use, simple to maintain.

Any suggestion or complain ? Feel to use github issue tracker.

## Licence

This code can be reused, remixed and whatever according to the 
[BEERWARE Licence](LICENCE).

## Author

Floréal Toumikian \<floreal at nimukaito dot net\>


