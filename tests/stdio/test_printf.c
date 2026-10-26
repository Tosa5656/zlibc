#include <limits.h>
#include <string.h>

#include "test.h"

void test_stdio_printf(void)
{
	char buffer[256];
	int written;
	int n;

	test_suite("stdio-printf");

	CHECK_INT(sprintf(buffer, "hello %s", "world"), 11);
	CHECK_STR(buffer, "hello world");

	CHECK_INT(sprintf(buffer, "d=%d i=%i u=%u", -42, 42, 42), 16);
	CHECK_STR(buffer, "d=-42 i=42 u=42");

	sprintf(buffer, "%x %X %o", 255, 255, 255);
	CHECK_STR(buffer, "ff FF 377");

	sprintf(buffer, "%s", NULL);
	CHECK_STR(buffer, "(null)");

	sprintf(buffer, "100%% %c", 'Z');
	CHECK_STR(buffer, "100% Z");

	sprintf(buffer, "%8d|%-8d|%08d", 1234, 1234, 1234);
	CHECK_STR(buffer, "    1234|1234    |00001234");

	sprintf(buffer, "%+d % d %+d", 5, 5, -7);
	CHECK_STR(buffer, "+5  5 -7");

	sprintf(buffer, "%#x %#o", 42, 42);
	CHECK_STR(buffer, "0x2a 052");

	sprintf(buffer, "%.5d %.2s", 42, "abcdef");
	CHECK_STR(buffer, "00042 ab");

	sprintf(buffer, "%5.2f", 3.14159);
	CHECK_STR(buffer, " 3.14");

	sprintf(buffer, "%f", 2.5);
	CHECK_STR(buffer, "2.500000");

	sprintf(buffer, "%e", 12345.678);
	CHECK_STR(buffer, "1.234568e+04");

	sprintf(buffer, "%.3e", 0.0);
	CHECK_STR(buffer, "0.000e+00");

	sprintf(buffer, "%g %g %g", 100000.0, 1000000.0, 0.0001);
	CHECK_STR(buffer, "100000 1e+06 0.0001");

	sprintf(buffer, "%g", 0.0);
	CHECK_STR(buffer, "0");

	sprintf(buffer, "%lld %zu", (long long)LLONG_MIN, (size_t)12345);
	CHECK_STR(buffer, "-9223372036854775808 12345");

	sprintf(buffer, "%lx", (unsigned long)-1);
	CHECK_STR(buffer, "ffffffffffffffff");

	sprintf(buffer, "%hhx %hd", (unsigned char)0xAB, (short)-2);
	CHECK_STR(buffer, "ab -2");

	sprintf(buffer, "%*d", 5, 42);
	CHECK_STR(buffer, "   42");

	sprintf(buffer, "%.*f", 3, 2.25);
	CHECK_STR(buffer, "2.250");

	sprintf(buffer, "%.2f", 1.2345);
	CHECK_STR(buffer, "1.23");

	written = sprintf(buffer, "abc%n", &n);
	CHECK_INT(written, 3);
	CHECK_INT(n, 3);

	written = snprintf(buffer, 5, "%d", 123456);
	CHECK_INT(written, 6);
	CHECK_SIZE(strlen(buffer), 4);
	CHECK_STR(buffer, "1234");

	CHECK_INT(snprintf(buffer, 0, "%d", 123456), 6);
	CHECK_INT(snprintf(buffer, sizeof buffer, "%s!", "ok"), 3);
	CHECK_STR(buffer, "ok!");

	CHECK(fprintf(stdout, "stdout ready\n") > 0);
}
