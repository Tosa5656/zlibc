#include "test.h"

void test_strrchr(void)
{
	const char text[] = "abcabc";
	const char empty[] = "";

	test_suite("strrchr");

	CHECK_PTR(strrchr(text, 'a'), text + 3);
	CHECK_PTR(strrchr(text, 'b'), text + 4);
	CHECK_PTR(strrchr(text, 'c'), text + 5);
	CHECK(strrchr(text, 'z') == NULL);

	CHECK_PTR(strrchr(text, '\0'), text + 6);
	CHECK_PTR(strrchr(empty, '\0'), empty);
	CHECK(strrchr(empty, 'a') == NULL);

	CHECK_PTR(strrchr("xyz", 'y'), "xyz" + 1);
}
