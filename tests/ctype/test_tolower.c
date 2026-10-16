#include "test.h"

void test_tolower(void)
{
	static const int ranges[] = { 'A', 'Z' };

	test_suite("tolower");

	test_ctype_case("tolower", tolower, ranges, 1, 'a' - 'A');

	CHECK_INT(tolower('A'), 'a');
	CHECK_INT(tolower('Z'), 'z');
	CHECK_INT(tolower('a'), 'a');
	CHECK_INT(tolower('0'), '0');
	CHECK_INT(tolower(' '), ' ');
	CHECK_INT(tolower('\n'), '\n');
	CHECK_INT(tolower(127), 127);
	CHECK_INT(tolower(EOF), EOF);
}
