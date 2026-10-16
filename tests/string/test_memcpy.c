#include "test.h"

void test_memcpy(void)
{
	char destination[16];
	const char source[] = "hello, world";
	unsigned char pattern_source[256];
	unsigned char pattern_destination[256];

	test_suite("memcpy");

	memset(destination, 0x11, sizeof(destination));
	CHECK_PTR(memcpy(destination, source, sizeof(source)), destination);
	CHECK_STR(destination, "hello, world");
	CHECK(destination[12] == '\0');
	CHECK(destination[13] == 0x11);
	CHECK(destination[15] == 0x11);

	memset(destination, 0x22, sizeof(destination));
	CHECK_PTR(memcpy(destination, source, 0), destination);
	CHECK(test_bytes_all(destination, 0x22, sizeof(destination)));

	for (size_t i = 0; i < sizeof(pattern_source); i++)
	{
		pattern_source[i] = (unsigned char)(i * 7u + 3u);
	}

	memset(pattern_destination, 0, sizeof(pattern_destination));
	CHECK_PTR(memcpy(pattern_destination, pattern_source, sizeof(pattern_source)),
		pattern_destination);
	CHECK(test_bytes_eq(pattern_destination, pattern_source, sizeof(pattern_source)));
}
