#include "test.h"

void test_toupper(void)
{
	static const int ranges[] = { 'a', 'z' };

	test_suite("toupper");

	test_ctype_case("toupper", toupper, ranges, 1, 'A' - 'a');

	CHECK_INT(toupper('a'), 'A');
	CHECK_INT(toupper('z'), 'Z');
	CHECK_INT(toupper('A'), 'A');
	CHECK_INT(toupper('0'), '0');
	CHECK_INT(toupper(' '), ' ');
	CHECK_INT(toupper('\n'), '\n');
	CHECK_INT(toupper(127), 127);
	CHECK_INT(toupper(EOF), EOF);
}
