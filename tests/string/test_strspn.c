#include "test.h"

void test_strspn(void)
{
	test_suite("strspn");

	CHECK_SIZE(strspn("abcde", "abcd"), 4);
	CHECK_SIZE(strspn("aaa", "a"), 3);
	CHECK_SIZE(strspn("abc", ""), 0);
	CHECK_SIZE(strspn("", "abc"), 0);
	CHECK_SIZE(strspn("xyz", "abc"), 0);
	CHECK_SIZE(strspn("abc", "abcdef"), 3);
	CHECK_SIZE(strspn("", ""), 0);
}
