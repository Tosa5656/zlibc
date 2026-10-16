#include "test.h"

void test_strstr(void)
{
	const char text[] = "the quick brown fox";
	const char repeats[] = "aaaab";

	test_suite("strstr");

	CHECK_PTR(strstr(text, "the"), text);
	CHECK_PTR(strstr(text, "quick"), text + 4);
	CHECK_PTR(strstr(text, "brown"), text + 10);
	CHECK_PTR(strstr(text, "fox"), text + 16);
	CHECK(strstr(text, "cat") == NULL);
	CHECK(strstr(text, "the quick brown fox jumps") == NULL);

	CHECK_PTR(strstr(text, ""), text);
	CHECK_PTR(strstr("", ""), "");
	CHECK(strstr("", "a") == NULL);

	CHECK_PTR(strstr(repeats, "aaab"), repeats + 1);
	CHECK_PTR(strstr("aab", "ab"), "aab" + 1);
}
