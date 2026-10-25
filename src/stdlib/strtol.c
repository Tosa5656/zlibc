#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <errors.h>

#define INT_LONG_MAX_DIGIT  (((unsigned long)-1) >> 1)
#define INT_LONG_NEG_LIMIT  (INT_LONG_MAX_DIGIT + 1)
#define INT_ULONG_MAX_DIGIT ((unsigned long)-1)

#define INT_LLONG_MAX_DIGIT  (((unsigned long long)-1) >> 1)
#define INT_LLONG_NEG_LIMIT  (INT_LLONG_MAX_DIGIT + 1)
#define INT_ULLONG_MAX_DIGIT ((unsigned long long)-1)

static int int_digit_value(int character, int base)
{
	int value;

	if (isdigit(character))
	{
		value = character - '0';
	}
	else if (isalpha(character))
	{
		value = (tolower(character) - 'a') + 10;
	}
	else
	{
		return -1;
	}

	return (value < base) ? value : -1;
}

typedef struct
{
	unsigned long long magnitude;
	int negative;
	int out_of_range;
} int_parse_result_t;

static void int_parse_core(int_parse_result_t *result, const char *nptr, char **endptr, int base_in, unsigned long long positive_limit, unsigned long long negative_limit)
{
	const char *cursor = nptr;
	int base = base_in;
	int consumed_digit = 0;

	result->magnitude = 0ULL;
	result->negative = 0;
	result->out_of_range = 0;

	while (isspace((unsigned char)*cursor))
	{
		cursor++;
	}

	if (*cursor == '+')
	{
		cursor++;
	}
	else if (*cursor == '-')
	{
		result->negative = 1;
		cursor++;
	}

	if (base == 16 && cursor[0] == '0' && (cursor[1] == 'x' || cursor[1] == 'X') && int_digit_value(cursor[2], 16) >= 0)
	{
		base = 16;
		cursor += 2;
	}
	else if (base == 0)
	{
		if (cursor[0] == '0')
		{
			if ((cursor[1] == 'x' || cursor[1] == 'X') && int_digit_value(cursor[2], 16) >= 0)
			{
				base = 16;
				cursor += 2;
			}
			else
			{
				base = 8;
			}
		}
		else
		{
			base = 10;
		}
	}

	unsigned long long magnitude_limit = result->negative ? negative_limit : positive_limit;

	for (;;)
	{
		int digit = int_digit_value((unsigned char)*cursor, base);

		if (digit < 0)
		{
			break;
		}

		consumed_digit = 1;

		if (result->out_of_range)
		{
			result->magnitude = magnitude_limit;
		}
		else if (result->magnitude > (magnitude_limit - (unsigned long long)digit) / (unsigned long long)base)
		{
			result->magnitude = magnitude_limit;
			result->out_of_range = 1;
		}
		else
		{
			result->magnitude = result->magnitude * (unsigned long long)base + (unsigned long long)digit;
		}

		cursor++;
	}

	if (!consumed_digit)
	{
		if (endptr)
		{
			*endptr = (char *)nptr;
		}

		return;
	}

	if (endptr)
	{
		*endptr = (char *)cursor;
	}
}

static int int_base_invalid(int base)
{
	return base < 0 || base == 1 || base > 36;
}

long strtol(const char *nptr, char **endptr, int base)
{
	int_parse_result_t parse;
	unsigned long long magnitude;

	if (endptr)
	{
		*endptr = (char *)nptr;
	}

	if (int_base_invalid(base))
	{
		errno = EINVAL;

		return 0;
	}

	int_parse_core(&parse, nptr, endptr, base, INT_LONG_MAX_DIGIT, INT_LONG_NEG_LIMIT);

	if (parse.out_of_range)
	{
		errno = ERANGE;
	}

	magnitude = parse.negative ? (0ULL - parse.magnitude) : parse.magnitude;

	if ((long)magnitude < 0 && !parse.negative)
	{
		errno = ERANGE;

		return (long)INT_LONG_MAX_DIGIT;
	}

	return (long)magnitude;
}

unsigned long strtoul(const char *nptr, char **endptr, int base)
{
	int_parse_result_t parse;

	if (endptr)
	{
		*endptr = (char *)nptr;
	}

	if (int_base_invalid(base))
	{
		errno = EINVAL;

		return 0;
	}

	int_parse_core(&parse, nptr, endptr, base, INT_ULONG_MAX_DIGIT, INT_ULONG_MAX_DIGIT);

	if (parse.out_of_range)
	{
		errno = ERANGE;
	}

	if (parse.negative)
	{
		return (unsigned long)(0UL - (unsigned long)parse.magnitude);
	}

	return (unsigned long)parse.magnitude;
}

long long strtoll(const char *nptr, char **endptr, int base)
{
	int_parse_result_t parse;
	unsigned long long magnitude;

	if (endptr)
	{
		*endptr = (char *)nptr;
	}

	if (int_base_invalid(base))
	{
		errno = EINVAL;

		return 0;
	}

	int_parse_core(&parse, nptr, endptr, base, INT_LLONG_MAX_DIGIT, INT_LLONG_NEG_LIMIT);

	if (parse.out_of_range)
	{
		errno = ERANGE;
	}

	magnitude = parse.negative ? (0ULL - parse.magnitude) : parse.magnitude;

	if ((long long)magnitude < 0 && !parse.negative)
	{
		errno = ERANGE;

		return (long long)INT_LLONG_MAX_DIGIT;
	}

	return (long long)magnitude;
}

unsigned long long strtoull(const char *nptr, char **endptr, int base)
{
	int_parse_result_t parse;

	if (endptr)
	{
		*endptr = (char *)nptr;
	}

	if (int_base_invalid(base))
	{
		errno = EINVAL;

		return 0;
	}

	int_parse_core(&parse, nptr, endptr, base, INT_ULLONG_MAX_DIGIT, INT_ULLONG_MAX_DIGIT);

	if (parse.out_of_range)
	{
		errno = ERANGE;
	}

	if (parse.negative)
	{
		return 0ULL - parse.magnitude;
	}

	return parse.magnitude;
}
