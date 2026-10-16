#include "test.h"

void test_memset(void)
{
	unsigned char buffer[20];

	test_suite("memset");

	CHECK_PTR(memset(buffer, 0xAA, sizeof(buffer)), buffer);
	CHECK(test_bytes_all(buffer, 0xAA, sizeof(buffer)));

	CHECK_PTR(memset(buffer, 0, 4), buffer);
	CHECK(test_bytes_all(buffer, 0, 4));
	CHECK(test_bytes_all(buffer + 4, 0xAA, sizeof(buffer) - 4));

	CHECK_PTR(memset(buffer, 0x5A, 0), buffer);
	CHECK(test_bytes_all(buffer + 4, 0xAA, sizeof(buffer) - 4));

	CHECK_PTR(memset(buffer, 0x1FF, 1), buffer);
	CHECK(buffer[0] == 0xFF);
}
