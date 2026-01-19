# C Development Kit: Error

The C Development Kit (CDK) is a collection of lightweight, MIT licensed libraries to make C development on Linux simpler and more consistent.

## Intro

Wouldn't it be awesome if we had errors with messages, try, catch, and even backtraces in C?

Wouldn't it be even more awesome if such a library were not bloated with `setjmp`, `malloc`, and similar monstrosities?

In fact, it would, so I created this simple library. It allows using an `errno` like mechanism with additional string messages, backtraces, and a try-catch mechanism, all in the form of a single header file. Feel free to just drop the library into your project to add a simple error stack to your code.

Usage example:

```c
#include <cdk_error.h>

cdk_error_t bar(void) {
  cdk_errno = cdk_errnos(EINVAL, "Something went wrong in bar");
  return cdk_errno;
}

void bar_cleanup(void) {}

cdk_error_t foo(void) {
  cdk_errno = bar();
  CDK_TRY(cdk_errno);

  return 0;

error_out:
  return cdk_errno;
}

int main(void) {
  char buf[2048];

  cdk_errno = bar();
  CDK_TRY(cdk_errno);

  cdk_errno = foo();
  CDK_TRY_CATCH(cdk_errno, error_bar_cleanup);

  return 0;

error_bar_cleanup:
  bar_cleanup();
error_out:
  cdk_error_dumps(cdk_errno, sizeof(buf), buf);
  return cdk_errno->code;
}
```

## Architecture overview

We use a few simple ideas in the library.

First: to avoid locks, we use `_Thread_local` storage, which allows us to drop locking entirely because each thread has its own error stack at the moment it is created.

Second: there is `struct Error`, which describes a generic error and can be used in three different modes. This is done because if you want the most speed on error handling, you do not want to use additional strings, hence the integer error type. We also have string and formatted string types. The integer type is the fastest, while the formatted string is the slowest.

Third: we gather backtraces manually. This gathering is hidden behind `CDK_TRY` and `CDK_TRY_CATCH`, so the user does not need to remember about it.

Fourth: all code is in a single header file, which makes it easy to drop into an application or a library. This way, every library or application has its own error stack, separated from the rest of the system. Because of that, we try to make `struct Error` as small as possible. On my amd64 PC it is 664 bytes. If you need to make it smaller, compile with `-DCDK_ERROR_OPTIMIZE=1`; on my amd64 machine this reduces a single error object to 48 bytes.

## Getting started

The library is header only. To use it, copy the single header file into your own project or library. By default, the library has the errno mechanism enabled, so you will need two definitions for errno: `cdk_errno` and `cdk_hidden_errno`.

```c
// myerror.h
#ifndef MYERROR_H
#define MYERROR_H

#define CDK_ERROR_FSTR_MAX 512
#define CDK_ERROR_BTRACE_MAX 32
#include "cdk_error.h"

#endif
```

```c
// myerror.c
#include "myerror.h"

_Thread_local cdk_error_t cdk_errno = NULL;
_Thread_local struct cdk_Error cdk_hidden_errno = {0};
```

Every file in your project includes `myerror.h`.

🔧 If you’d like to change the prefix (for example, from `cdk_` to `my_`), there’s a helper script:

```bash
python3 tools/change_prefix.py \
  --inf include/cdk_error.h \
  --out my_error.h \
  --old cdk --new my
```

## Why copy instead of link?

Unlike traditional libraries, `cdk_error` is designed to be embedded into each project separately. We do it in such way because every library or program should have its **own private error state**.

## Development workflow

For convenience, there’s an [Invoke](https://www.pyinvoke.org/) setup that automates common tasks:

```sh
inv install   # install meson, ninja, clang-format, clang-tidy, etc.
inv build     # configure and compile (add --debug, --tests, --examples)
inv test      # run test suite
inv format    # apply clang-format
inv lint      # run clang-tidy checks
inv clean     # remove build artifacts
```

## License

Released under the [MIT License](LICENSE) © 2026 Jakub Buczynski (KubaTaba1uga).
