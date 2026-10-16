#include "test.h"

static int test_ctype_in_ranges(int value, const int *ranges, size_t range_count)
{
	size_t index;

	for (index = 0; index < range_count; index++)
	{
		if (value >= ranges[index * 2] && value <= ranges[index * 2 + 1])
		{
			return 1;
		}
	}

	return 0;
}

void test_ctype_class(const char *function_name, int (*function)(int),
	const int *ranges, size_t range_count)
{
	int value;

	for (value = -1; value < 256; value++)
	{
		int expected = test_ctype_in_ranges(value, ranges, range_count);

		test_checks++;
		if ((function(value) != 0) != expected)
		{
			test_fail(__FILE__, __LINE__, "%s(%d): got %d, want %s",
				function_name, value, function(value), expected ? "nonzero" : "0");
		}
	}
}

void test_ctype_case(const char *function_name, int (*function)(int),
	const int *ranges, size_t range_count, int offset)
{
	int value;

	for (value = -1; value < 256; value++)
	{
		int expected = test_ctype_in_ranges(value, ranges, range_count)
			? value + offset
			: value;

		test_checks++;
		if (function(value) != expected)
		{
			test_fail(__FILE__, __LINE__, "%s(%d): got %d, want %d",
				function_name, value, function(value), expected);
		}
	}
}

void test_ctype(void)
{
	test_isalnum();
	test_isalpha();
	test_isblank();
	test_iscntrl();
	test_isdigit();
	test_isgraph();
	test_islower();
	test_isprint();
	test_ispunct();
	test_isspace();
	test_isupper();
	test_isxdigit();

	test_tolower();
	test_toupper();
}
