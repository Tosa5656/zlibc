#include "test.h"

void test_isalpha(void)
{
	static const int ranges[] = { 'A', 'Z', 'a', 'z' };

	test_suite("isalpha");

	test_ctype_class("isalpha", isalpha, ranges, 2);

	CHECK(isalpha('A'));
	CHECK(isalpha('Z'));
	CHECK(isalpha('a'));
	CHECK(isalpha('z'));

	CHECK(!isalpha('@'));
	CHECK(!isalpha('['));
	CHECK(!isalpha('`'));
	CHECK(!isalpha('{'));
	CHECK(!isalpha('0'));
	CHECK(!isalpha('9'));
	CHECK(!isalpha(' '));
	CHECK(!isalpha('\t'));
	CHECK(!isalpha('\0'));
}
