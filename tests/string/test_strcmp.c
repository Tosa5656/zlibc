#include "test.h"

void test_strcmp(void)
{
	test_suite("strcmp");

	CHECK_SIGN(strcmp("", ""), 0);
	CHECK_SIGN(strcmp("abc", "abc"), 0);
	CHECK_SIGN(strcmp("abc", "abd"), -1);
	CHECK_SIGN(strcmp("abd", "abc"), 1);
	CHECK_SIGN(strcmp("ab", "abc"), -1);
	CHECK_SIGN(strcmp("abc", "ab"), 1);
	CHECK_SIGN(strcmp("", "a"), -1);
	CHECK_SIGN(strcmp("a", ""), 1);
	CHECK_SIGN(strcmp("Z", "a"), -1);

	CHECK_SIGN(strcmp("\x80", "\x7F"), 1);
	CHECK_SIGN(strcmp("\x7F", "\x80"), -1);
	CHECK_SIGN(strcmp("\xFF", "\x01"), 1);
}
