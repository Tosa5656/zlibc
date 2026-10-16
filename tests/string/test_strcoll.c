#include "test.h"

void test_strcoll(void)
{
	test_suite("strcoll");

	CHECK_SIGN(strcoll("", ""), 0);
	CHECK_SIGN(strcoll("abc", "abc"), 0);
	CHECK_SIGN(strcoll("abc", "abd"), -1);
	CHECK_SIGN(strcoll("abd", "abc"), 1);
	CHECK_SIGN(strcoll("ab", "abc"), -1);
	CHECK_SIGN(strcoll("abc", "ab"), 1);
}
