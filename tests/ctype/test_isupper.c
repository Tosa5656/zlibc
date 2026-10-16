#include "test.h"

void test_isupper(void)
{
	static const int ranges[] = { 'A', 'Z' };

	test_suite("isupper");

	test_ctype_class("isupper", isupper, ranges, 1);

	CHECK(isupper('A'));
	CHECK(isupper('M'));
	CHECK(isupper('Z'));

	CHECK(!isupper('a'));
	CHECK(!isupper('z'));
	CHECK(!isupper('@'));
	CHECK(!isupper('['));
	CHECK(!isupper('0'));
	CHECK(!isupper(' '));
	CHECK(!isupper('\0'));
}
