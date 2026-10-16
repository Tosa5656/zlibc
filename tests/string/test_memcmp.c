#include "test.h"

void test_memcmp(void)
{
	const char full[] = "abcde";
	const char truncated[5] = {'a', 'b', 'c', '\0', 'X'};
	const unsigned char low[] = {0x01};
	const unsigned char high[] = {0xFF};

	test_suite("memcmp");

	CHECK_SIGN(memcmp(full, full, 5), 0);
	CHECK_SIGN(memcmp(full, "abcdx", 5), -1);
	CHECK_SIGN(memcmp("abcdx", full, 5), 1);
	CHECK_SIGN(memcmp(full, truncated, 5), 1);
	CHECK_SIGN(memcmp(truncated, full, 5), -1);
	CHECK_SIGN(memcmp(full, "abcde", 0), 0);

	CHECK_SIGN(memcmp(low, high, 1), -1);
	CHECK_SIGN(memcmp(high, low, 1), 1);
}
