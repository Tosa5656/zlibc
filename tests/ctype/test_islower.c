#include "test.h"

void test_islower(void)
{
	static const int ranges[] = { 'a', 'z' };

	test_suite("islower");

	test_ctype_class("islower", islower, ranges, 1);

	CHECK(islower('a'));
	CHECK(islower('m'));
	CHECK(islower('z'));

	CHECK(!islower('A'));
	CHECK(!islower('Z'));
	CHECK(!islower('`'));
	CHECK(!islower('{'));
	CHECK(!islower('0'));
	CHECK(!islower(' '));
	CHECK(!islower('\0'));
}
