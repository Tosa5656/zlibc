#include "test.h"

void test_isdigit(void)
{
	static const int ranges[] = { '0', '9' };

	test_suite("isdigit");

	test_ctype_class("isdigit", isdigit, ranges, 1);

	CHECK(isdigit('0'));
	CHECK(isdigit('5'));
	CHECK(isdigit('9'));

	CHECK(!isdigit('/'));
	CHECK(!isdigit(':'));
	CHECK(!isdigit('A'));
	CHECK(!isdigit('a'));
	CHECK(!isdigit(' '));
	CHECK(!isdigit('\0'));
}
