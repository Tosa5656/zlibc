#include "test.h"

void test_isprint(void)
{
	static const int ranges[] = { ' ', '~' };

	test_suite("isprint");

	test_ctype_class("isprint", isprint, ranges, 1);

	CHECK(isprint(' '));
	CHECK(isprint('!'));
	CHECK(isprint('0'));
	CHECK(isprint('A'));
	CHECK(isprint('a'));
	CHECK(isprint('~'));

	CHECK(!isprint('\t'));
	CHECK(!isprint('\n'));
	CHECK(!isprint('\v'));
	CHECK(!isprint('\0'));
	CHECK(!isprint(31));
	CHECK(!isprint(127));
	CHECK(!isprint(128));
}
