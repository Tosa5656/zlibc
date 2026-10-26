#include <limits.h>
#include <string.h>

#include "test.h"

void test_stdio_scanf_int(void)
{
	int a, b, n;
	long l;
	unsigned u;
	double d;

	test_suite("stdio-scanf-int");

	a = 0;
	CHECK_INT(sscanf("42", "%d", &a), 1);
	CHECK_INT(a, 42);

	CHECK_INT(sscanf("-17", "%d", &a), 1);
	CHECK_INT(a, -17);

	a = 0;
	CHECK_INT(sscanf("0x1F", "%i", &a), 1);
	CHECK_INT(a, 31);

	a = 0;
	CHECK_INT(sscanf("0755", "%i", &a), 1);
	CHECK_INT(a, 493);

	u = 0;
	CHECK_INT(sscanf("ff", "%x", &u), 1);
	CHECK_INT(u, 0xff);

	u = 0;
	CHECK_INT(sscanf("153", "%o", &u), 1);
	CHECK_INT(u, 0153);

	CHECK_INT(sscanf("  123  456 ", "%d %d", &a, &b), 2);
	CHECK_INT(a, 123);
	CHECK_INT(b, 456);

	CHECK_INT(sscanf("12:34", "%d:%d", &a, &b), 2);
	CHECK_INT(a, 12);
	CHECK_INT(b, 34);

	CHECK_INT(sscanf("123456", "%3d", &a), 1);
	CHECK_INT(a, 123);

	n = -1;
	CHECK_INT(sscanf("42", "%d%n", &a, &n), 1);
	CHECK_INT(a, 42);
	CHECK_INT(n, 2);

	n = -1;
	CHECK_INT(sscanf("   9", "%*d%n", &n), 0);
	CHECK_INT(n, 4);

	CHECK_INT(sscanf("junk 100", "%*s %d", &a), 1);
	CHECK_INT(a, 100);

	l = 0;
	CHECK_INT(sscanf("-9876543210", "%ld", &l), 1);
	CHECK_INT(l, -9876543210L);

	d = 0;
	CHECK_INT(sscanf("3.5", "%lf", &d), 1);
	CHECK_INT(d, 3.5);

	d = 0;
	CHECK_INT(sscanf("-2.5e1", "%lf", &d), 1);
	CHECK_INT(d, -25.0);

	CHECK_INT(sscanf("abc", "%d", &a), 0);
	CHECK_INT(sscanf("", "%d", &a), 0);
}
