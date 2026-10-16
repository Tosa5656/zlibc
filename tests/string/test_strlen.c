#include "test.h"

void test_strlen(void)
{
	char buffer[64];

	test_suite("strlen");

	CHECK_SIZE(strlen(""), 0);
	CHECK_SIZE(strlen("a"), 1);
	CHECK_SIZE(strlen("hello, world"), 12);

	memset(buffer, 'x', sizeof(buffer) - 1);
	buffer[sizeof(buffer) - 1] = '\0';
	CHECK_SIZE(strlen(buffer), sizeof(buffer) - 1);

	CHECK_SIZE(strlen("ab\0cd"), 2);
}
