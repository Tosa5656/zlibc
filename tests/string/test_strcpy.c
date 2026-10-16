#include "test.h"

void test_strcpy(void)
{
	char destination[16];

	test_suite("strcpy");

	memset(destination, 0x77, sizeof(destination));
	CHECK_PTR(strcpy(destination, "hello"), destination);
	CHECK_STR(destination, "hello");
	CHECK(destination[5] == '\0');
	CHECK(destination[6] == 0x77);
	CHECK(destination[15] == 0x77);

	memset(destination, 0x77, sizeof(destination));
	CHECK_PTR(strcpy(destination, ""), destination);
	CHECK(destination[0] == '\0');
	CHECK(destination[1] == 0x77);

	strcpy(destination, "long string");
	strcpy(destination, "short");
	CHECK_STR(destination, "short");
}
