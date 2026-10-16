#include "test.h"

void test_strcspn(void)
{
	test_suite("strcspn");

	CHECK_SIZE(strcspn("abcde", "cd"), 2);
	CHECK_SIZE(strcspn("hello", ""), 5);
	CHECK_SIZE(strcspn("", "xyz"), 0);
	CHECK_SIZE(strcspn("aaa", "a"), 0);
	CHECK_SIZE(strcspn("abcxyz", "z"), 5);
	CHECK_SIZE(strcspn("", ""), 0);
}
