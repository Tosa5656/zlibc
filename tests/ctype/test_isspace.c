#include "test.h"

void test_isspace(void)
{
	/* Space and the standard white-space controls \t \n \v \f \r. */
	static const int ranges[] = { '\t', '\r', ' ', ' ' };

	test_suite("isspace");

	test_ctype_class("isspace", isspace, ranges, 2);

	CHECK(isspace(' '));
	CHECK(isspace('\t'));
	CHECK(isspace('\n'));
	CHECK(isspace('\v'));
	CHECK(isspace('\f'));
	CHECK(isspace('\r'));

	CHECK(!isspace('\0'));
	CHECK(!isspace('0'));
	CHECK(!isspace('A'));
	CHECK(!isspace('a'));
	CHECK(!isspace('!'));
	CHECK(!isspace(31));
	CHECK(!isspace(127));
}
