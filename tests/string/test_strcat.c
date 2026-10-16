#include "test.h"

void test_strcat(void)
{
	char destination[16];

	test_suite("strcat");

	memset(destination, 0x77, sizeof(destination));
	strcpy(destination, "foo");
	CHECK_PTR(strcat(destination, "bar"), destination);
	CHECK_STR(destination, "foobar");
	CHECK(destination[6] == '\0');
	CHECK(destination[7] == 0x77);

	strcat(destination, "");
	CHECK_STR(destination, "foobar");

	memset(destination, 0x77, sizeof(destination));
	strcpy(destination, "");
	strcat(destination, "x");
	CHECK_STR(destination, "x");
	CHECK(destination[2] == 0x77);

	memset(destination, 0x77, sizeof(destination));
	strcpy(destination, "");
	strcat(destination, "");
	CHECK(destination[0] == '\0');
	CHECK(destination[1] == 0x77);
}
