#include <stdarg.h>

#include "test.h"

int test_checks = 0;
int test_failures = 0;
int test_passed = 0;
int test_failed = 0;

static const char *test_name = NULL;
static int test_name_failures = 0;

void test_finish(void)
{
	if (test_name == NULL)
	{
		return;
	}

	if (test_name_failures == 0)
	{
		printf(" OK\n");
		test_passed++;
	}
	else
	{
		test_failed++;
	}

	test_name = NULL;
	test_name_failures = 0;
}

void test_summary(void)
{
	printf("%d passed, %d failed\n", test_passed, test_failed);
}

void test_suite(const char *name)
{
	test_finish();

	test_name = name;
	test_name_failures = 0;

	printf("-- %s", name);
	fflush(stdout);
}

void test_fail(const char *file, int line, const char *format, ...)
{
	va_list arguments;

	test_failures++;

	if (test_name != NULL && test_name_failures == 0)
	{
		printf(" FAIL\n");
	}

	test_name_failures++;

	printf("  FAIL [%s:%d] ", file, line);

	va_start(arguments, format);
	vprintf(format, arguments);
	va_end(arguments);

	printf("\n");
}

int test_streq(const char *string1, const char *string2)
{
	if (string1 == NULL || string2 == NULL)
	{
		return string1 == string2;
	}

	while (*string1 != '\0' && *string1 == *string2)
	{
		string1++;
		string2++;
	}

	return (unsigned char)*string1 == (unsigned char)*string2;
}

int test_bytes_eq(const void *bytes1, const void *bytes2, size_t count)
{
	const unsigned char *left = (const unsigned char *)bytes1;
	const unsigned char *right = (const unsigned char *)bytes2;

	for (size_t i = 0; i < count; i++)
	{
		if (left[i] != right[i])
		{
			return 0;
		}
	}

	return 1;
}

int test_bytes_all(const void *bytes, unsigned char value, size_t count)
{
	const unsigned char *buffer = (const unsigned char *)bytes;

	for (size_t i = 0; i < count; i++)
	{
		if (buffer[i] != value)
		{
			return 0;
		}
	}

	return 1;
}
