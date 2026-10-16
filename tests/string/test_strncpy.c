#include "test.h"

void test_strncpy(void)
{
	char destination[8];

	test_suite("strncpy");

	memset(destination, 0x77, sizeof(destination));
	CHECK_PTR(strncpy(destination, "hi", 6), destination);
	CHECK_STR(destination, "hi");
	CHECK(test_bytes_all(destination + 2, 0, 4));
	CHECK(destination[6] == 0x77);

	memset(destination, 0x77, sizeof(destination));
	CHECK_PTR(strncpy(destination, "hello", 5), destination);
	CHECK(test_bytes_eq(destination, "hello", 5));
	CHECK(destination[5] == 0x77);

	memset(destination, 0x77, sizeof(destination));
	CHECK_PTR(strncpy(destination, "hello", 3), destination);
	CHECK(test_bytes_eq(destination, "hel", 3));
	CHECK(destination[3] == 0x77);

	memset(destination, 0x77, sizeof(destination));
	CHECK_PTR(strncpy(destination, "ab", 0), destination);
	CHECK(test_bytes_all(destination, 0x77, sizeof(destination)));
}
