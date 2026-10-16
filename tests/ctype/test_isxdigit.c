#include "test.h"

void test_isxdigit(void)
{
	static const int ranges[] = { '0', '9', 'A', 'F', 'a', 'f' };

	test_suite("isxdigit");

	test_ctype_class("isxdigit", isxdigit, ranges, 3);

	CHECK(isxdigit('0'));
	CHECK(isxdigit('9'));
	CHECK(isxdigit('A'));
	CHECK(isxdigit('F'));
	CHECK(isxdigit('a'));
	CHECK(isxdigit('f'));

	CHECK(!isxdigit('/'));
	CHECK(!isxdigit(':'));
	CHECK(!isxdigit('@'));
	CHECK(!isxdigit('G'));
	CHECK(!isxdigit('`'));
	CHECK(!isxdigit('g'));
	CHECK(!isxdigit(' '));
	CHECK(!isxdigit('\0'));
}
