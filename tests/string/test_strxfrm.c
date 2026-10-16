#include "test.h"

void test_strxfrm(void)
{
	char destination[16];

	test_suite("strxfrm");

	memset(destination, 0x77, sizeof(destination));
	CHECK_SIZE(strxfrm(destination, "abc", sizeof(destination)), 3);
	CHECK_STR(destination, "abc");
	CHECK(destination[4] == 0x77);

	memset(destination, 0x77, sizeof(destination));
	CHECK_SIZE(strxfrm(destination, "abcdef", 4), 6);
	CHECK(test_bytes_eq(destination, "abc", 3));
	CHECK(destination[3] == '\0');
	CHECK(destination[4] == 0x77);

	memset(destination, 0x77, sizeof(destination));
	CHECK_SIZE(strxfrm(destination, "abc", 1), 3);
	CHECK(destination[0] == '\0');
	CHECK(destination[1] == 0x77);

	memset(destination, 0x77, sizeof(destination));
	CHECK_SIZE(strxfrm(destination, "abc", 0), 3);
	CHECK(test_bytes_all(destination, 0x77, sizeof(destination)));
	CHECK_SIZE(strxfrm(NULL, "abc", 0), 3);

	memset(destination, 0x77, sizeof(destination));
	CHECK_SIZE(strxfrm(destination, "", sizeof(destination)), 0);
	CHECK(destination[0] == '\0');
	CHECK(destination[1] == 0x77);
}
