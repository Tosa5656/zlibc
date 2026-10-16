#include "test.h"

void test_iscntrl(void)
{
	/* NUL..US and DEL. */
	static const int ranges[] = { 0, 31, 127, 127 };

	test_suite("iscntrl");

	test_ctype_class("iscntrl", iscntrl, ranges, 2);

	CHECK(iscntrl(0));
	CHECK(iscntrl('\n'));
	CHECK(iscntrl('\r'));
	CHECK(iscntrl('\t'));
	CHECK(iscntrl(31));
	CHECK(iscntrl(127));

	CHECK(!iscntrl(' '));
	CHECK(!iscntrl('!'));
	CHECK(!iscntrl('0'));
	CHECK(!iscntrl('a'));
	CHECK(!iscntrl(128));
	CHECK(!iscntrl(255));
}
