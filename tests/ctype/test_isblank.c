#include "test.h"

void test_isblank(void)
{
	static const int ranges[] = { ' ', ' ', '\t', '\t' };

	test_suite("isblank");

	test_ctype_class("isblank", isblank, ranges, 2);

	CHECK(isblank(' '));
	CHECK(isblank('\t'));

	CHECK(!isblank('\n'));
	CHECK(!isblank('\v'));
	CHECK(!isblank('\f'));
	CHECK(!isblank('\r'));
	CHECK(!isblank('\0'));
	CHECK(!isblank('a'));
	CHECK(!isblank('0'));
}
