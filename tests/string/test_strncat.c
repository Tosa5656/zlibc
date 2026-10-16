#include "test.h"

void test_strncat(void)
{
	char destination[16];

	test_suite("strncat");

	memset(destination, 0x77, sizeof(destination));
	strcpy(destination, "foo");
	CHECK_PTR(strncat(destination, "barbar", 3), destination);
	CHECK_STR(destination, "foobar");
	CHECK(destination[6] == '\0');
	CHECK(destination[7] == 0x77);

	strncat(destination, "!", 10);
	CHECK_STR(destination, "foobar!");

	CHECK_PTR(strncat(destination, "zzz", 0), destination);
	CHECK_STR(destination, "foobar!");

	memset(destination, 0x77, sizeof(destination));
	strcpy(destination, "");
	strncat(destination, "abc", 10);
	CHECK_STR(destination, "abc");
	CHECK(destination[4] == 0x77);
}
