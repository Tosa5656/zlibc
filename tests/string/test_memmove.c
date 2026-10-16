#include "test.h"

void test_memmove(void)
{
	char buffer[16];
	char other[8];

	test_suite("memmove");

	memcpy(buffer, "abcdef", 7);
	memset(other, 0x11, sizeof(other));
	CHECK_PTR(memmove(other, buffer, 7), other);
	CHECK(test_bytes_eq(other, buffer, 7));

	memcpy(buffer, "abcdefgh", 9);
	CHECK_PTR(memmove(buffer + 2, buffer, 6), buffer + 2);
	CHECK_STR(buffer, "ababcdef");
	CHECK(buffer[8] == '\0');

	memcpy(buffer, "abcdefgh", 9);
	CHECK_PTR(memmove(buffer, buffer + 2, 6), buffer);
	CHECK(test_bytes_eq(buffer, "cdefghgh", 8));
	CHECK(buffer[8] == '\0');

	memcpy(buffer, "abcdefgh", 9);
	CHECK_PTR(memmove(buffer, buffer + 4, 0), buffer);
	CHECK_STR(buffer, "abcdefgh");
	CHECK_PTR(memmove(buffer, buffer, 4), buffer);
	CHECK_STR(buffer, "abcdefgh");
}
