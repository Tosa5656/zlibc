#include <limits.h>
#include <string.h>

#include "test.h"

void test_stdio_scanf_str(void)
{
	char text[64];
	char a2[8], b2[8];
	int a;
	char c;

	test_suite("stdio-scanf-str");

	text[0] = 0;
	CHECK_INT(sscanf("  hello world  ", "%63s", text), 1);
	CHECK_STR(text, "hello");

	text[0] = 0;
	CHECK_INT(sscanf("word\t tab", "%s", text), 1);
	CHECK_STR(text, "word");

	a2[0] = 0;
	b2[0] = 0;
	CHECK_INT(sscanf("one two", "%7s %7s", a2, b2), 2);
	CHECK_STR(a2, "one");
	CHECK_STR(b2, "two");

	c = 0;
	CHECK_INT(sscanf(" a", "%c", &c), 1);
	CHECK_INT(c, ' ');

	CHECK_INT(sscanf(" ab", " %c", &c), 1);
	CHECK_INT(c, 'a');

	a2[0] = 0;
	b2[0] = 0;
	CHECK_INT(sscanf("ab cd", "%2c%2c", a2, b2), 2);
	CHECK_INT(a2[0], 'a');
	CHECK_INT(a2[1], 'b');
	CHECK_INT(b2[0], ' ');
	CHECK_INT(b2[1], 'c');

	a2[0] = 0;
	CHECK_INT(sscanf("bacon eggs", "%5[a b]", a2), 1);
	CHECK_STR(a2, "bacon");

	a2[0] = 0;
	CHECK_INT(sscanf("bacon soup", "%63[^s]", a2), 1);
	CHECK_STR(a2, "bacon ");

	a2[0] = 0;
	a = 0;
	CHECK_INT(sscanf("key=42", "key=%d", &a), 1);
	CHECK_INT(a, 42);

	CHECK_INT(sscanf("abc", "[", &(char){0}), 0);
}
