#include "test.h"

void test_strchr(void)
{
	const char text[] = "abcabc";
	const char empty[] = "";
	const char high[] = "\x80x";

	test_suite("strchr");

	CHECK_PTR(strchr(text, 'a'), text);
	CHECK_PTR(strchr(text, 'b'), text + 1);
	CHECK_PTR(strchr(text, 'c'), text + 2);
	CHECK(strchr(text, 'z') == NULL);

	CHECK_PTR(strchr(text, '\0'), text + 6);
	CHECK_PTR(strchr(empty, '\0'), empty);
	CHECK(strchr(empty, 'a') == NULL);

	CHECK_PTR(strchr(high, 0x80), high);
	CHECK_PTR(strchr(high, -128), high);
}
