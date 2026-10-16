#include "test.h"

void test_isgraph(void)
{
	/* Printable characters excluding the space. */
	static const int ranges[] = { '!', '~' };

	test_suite("isgraph");

	test_ctype_class("isgraph", isgraph, ranges, 1);

	CHECK(isgraph('!'));
	CHECK(isgraph('0'));
	CHECK(isgraph('A'));
	CHECK(isgraph('a'));
	CHECK(isgraph('~'));

	CHECK(!isgraph(' '));
	CHECK(!isgraph('\t'));
	CHECK(!isgraph('\n'));
	CHECK(!isgraph('\0'));
	CHECK(!isgraph(31));
	CHECK(!isgraph(127));
	CHECK(!isgraph(128));
}
