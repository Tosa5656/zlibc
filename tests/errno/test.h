#ifndef ZLIBC_ERRNO_TEST_H
#define ZLIBC_ERRNO_TEST_H

#include "../test.h"
#include "../../include/errno.h"
#include "../../include/errors.h"

#include <limits.h>

void test_errno(void);

void test_errno_macro(void);
void test_errno_location(void);
void test_error_constants(void);
void test_syscall_ret(void);

#endif
