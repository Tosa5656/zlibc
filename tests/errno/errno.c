#include "test.h"

void test_errno(void)
{
	test_errno_macro();
	test_errno_location();
	test_error_constants();
	test_syscall_ret();
}
