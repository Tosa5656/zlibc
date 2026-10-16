#include "test.h"

void test_strpbrk(void)
{
	const char text[] = "hello world";

	test_suite("strpbrk");

	CHECK_PTR(strpbrk(text, "lo"), text + 2);
	CHECK_PTR(strpbrk(text, "w"), text + 6);
	CHECK_PTR(strpbrk(text, "d"), text + 10);
	CHECK(strpbrk(text, "xyz") == NULL);
	CHECK(strpbrk(text, "") == NULL);
	CHECK(strpbrk("", "abc") == NULL);
}
