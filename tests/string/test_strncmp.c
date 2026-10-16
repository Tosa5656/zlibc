#include "test.h"

void test_strncmp(void)
{
	test_suite("strncmp");

	CHECK_SIGN(strncmp("abc", "abc", 3), 0);
	CHECK_SIGN(strncmp("abc", "abd", 3), -1);
	CHECK_SIGN(strncmp("abd", "abc", 3), 1);
	CHECK_SIGN(strncmp("abc", "xyz", 0), 0);

	CHECK_SIGN(strncmp("abc", "abd", 2), 0);
	CHECK_SIGN(strncmp("abc", "xyz", 3), -1);

	CHECK_SIGN(strncmp("abc", "ab", 3), 1);
	CHECK_SIGN(strncmp("ab", "abc", 3), -1);
	CHECK_SIGN(strncmp("abc", "abcd", 4), -1);

	CHECK_SIGN(strncmp("abcd", "abce", 3), 0);

	CHECK_SIGN(strncmp("\x80", "\x7F", 1), 1);
	CHECK_SIGN(strncmp("\x7F\x80", "\x7F\x01", 2), 1);
}
