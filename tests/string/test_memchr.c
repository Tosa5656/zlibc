#include "test.h"

void test_memchr(void)
{
	const char text[] = "abcabc";
	const char empty[] = "";
	const unsigned char binary[] = {0x00, 0x80, 0xFF};

	test_suite("memchr");

	CHECK_PTR(memchr(text, 'a', 6), text);
	CHECK_PTR(memchr(text, 'b', 6), text + 1);
	CHECK_PTR(memchr(text, 'c', 6), text + 2);
	CHECK(memchr(text, 'z', 6) == NULL);
	CHECK(memchr(text, 'z', 0) == NULL);

	CHECK_PTR(memchr(text, '\0', 7), text + 6);
	CHECK(memchr(text, '\0', 6) == NULL);

	CHECK(memchr(empty, 'a', 1) == NULL);
	CHECK_PTR(memchr(empty, '\0', 1), empty);

	CHECK_PTR(memchr(binary, 0x80, 3), binary + 1);
	CHECK_PTR(memchr(binary, -1, 3), binary + 2);
	CHECK_PTR(memchr(binary, 0, 3), binary);
}
