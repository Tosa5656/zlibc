#include "test.h"

void test_isalnum(void)
{
	static const int ranges[] = { '0', '9', 'A', 'Z', 'a', 'z' };

	test_suite("isalnum");

	test_ctype_class("isalnum", isalnum, ranges, 3);

	CHECK(isalnum('0'));
	CHECK(isalnum('9'));
	CHECK(isalnum('A'));
	CHECK(isalnum('Z'));
	CHECK(isalnum('a'));
	CHECK(isalnum('z'));

	CHECK(!isalnum('/'));
	CHECK(!isalnum(':'));
	CHECK(!isalnum('@'));
	CHECK(!isalnum('['));
	CHECK(!isalnum('`'));
	CHECK(!isalnum('{'));
	CHECK(!isalnum(' '));
	CHECK(!isalnum('\n'));
	CHECK(!isalnum('\0'));
}
