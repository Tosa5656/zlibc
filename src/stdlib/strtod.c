#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <errors.h>
#include <float.h>

#define STRTOD_DEC_MANTISSA_CAP		(((unsigned long long)-1) - 9) / 10
#define STRTOD_HEX_MANTISSA_CAP		(((unsigned long long)-1) - 15) / 16
#define STRTOD_EXPONENT_CAP			15000LL
#define STRTOD_DEC_EXPONENT_LIMIT	5000LL
#define STRTOD_HEX_EXPONENT_LIMIT	17000LL
#define STRTOD_POW10_CHUNK			27LL
#define STRTOD_POW2_CHUNK			62LL

typedef struct
{
	unsigned long long mantissa;
	long long start_index;
	long long absorbed;
	long long integer_digits;
	long long frac_seen;
	long long exponent;
	int negative;
} strtod_state_t;

static int strtod_lower(int character)
{
	return (character >= 'A' && character <= 'Z') ? character + ('a' - 'A') : character;
}

static int strtod_hex_value(int character, int *value_out)
{
	int lowered = strtod_lower((unsigned char)character);

	if (isdigit(lowered))
	{
		*value_out = lowered - '0';

		return 1;
	}

	if (lowered >= 'a' && lowered <= 'f')
	{
		*value_out = lowered - 'a' + 10;

		return 1;
	}

	return 0;
}

static long long strtod_parse_exponent(const char *cursor, long long *value_out)
{
	int negative = 0;
	long long consumed = 0;
	long long value = 0;
	int saw_digit = 0;

	if (*cursor == '+' || *cursor == '-')
	{
		negative = (*cursor == '-');
		cursor++;
		consumed++;
	}

	while (isdigit((unsigned char)*cursor))
	{
		if (value < STRTOD_EXPONENT_CAP)
		{
			value = value * 10 + (long long)(*cursor - '0');

			if (value > STRTOD_EXPONENT_CAP)
			{
				value = STRTOD_EXPONENT_CAP;
			}
		}

		saw_digit = 1;
		consumed++;
		cursor++;
	}

	if (!saw_digit)
	{
		return 0;
	}

	*value_out = negative ? -value : value;

	return consumed;
}

static void strtod_scale(long double *value, long long exponent, long double chunk_factor, long long chunk_power, long double unit, int *overflow, int *underflow)
{
	*overflow = 0;
	*underflow = 0;

	while (exponent >= chunk_power)
	{
		*value *= chunk_factor;

		if (*value > LDBL_MAX)
		{
			*overflow = 1;

			return;
		}

		exponent -= chunk_power;
	}

	while (exponent > 0)
	{
		*value *= unit;

		if (*value > LDBL_MAX)
		{
			*overflow = 1;

			return;
		}

		exponent--;
	}

	while (exponent <= -chunk_power)
	{
		*value /= chunk_factor;
		exponent += chunk_power;

		if (*value == 0.0L)
		{
			*underflow = 1;

			return;
		}
	}

	while (exponent < 0)
	{
		*value /= unit;
		exponent++;

		if (*value == 0.0L)
		{
			*underflow = 1;

			return;
		}
	}
}

long double strtold(const char *nptr, char **endptr)
{
	const char *cursor = nptr;
	strtod_state_t state = {0, 0, 0, 0, 0, 0, 0};
	unsigned long long mantissa_cap = STRTOD_DEC_MANTISSA_CAP;
	unsigned long long digit_base = 10ULL;
	long double unit = 10.0L;
	long double chunk_factor = 1e27L;
	long long chunk_power = STRTOD_POW10_CHUNK;
	long long exponent_limit = STRTOD_DEC_EXPONENT_LIMIT;
	long double result;
	int is_hex = 0;
	int saw_point = 0;
	int saw_digit = 0;
	int started = 0;
	int overflowed;
	int underflowed;

	if (endptr)
	{
		*endptr = (char *)nptr;
	}

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
		state.negative = 1;
		cursor++;
	}

	if (strtod_lower(cursor[0]) == 'i' && strtod_lower(cursor[1]) == 'n' && strtod_lower(cursor[2]) == 'f')
	{
		const char *end_cursor = cursor + 3;

		if (strtod_lower(end_cursor[0]) == 'i' && strtod_lower(end_cursor[1]) == 'n' && strtod_lower(end_cursor[2]) == 'i' && strtod_lower(end_cursor[3]) == 't' && strtod_lower(end_cursor[4]) == 'y')
		{
			end_cursor += 5;
		}

		if (endptr)
		{
			*endptr = (char *)end_cursor;
		}

		return state.negative ? -__builtin_infl() : __builtin_infl();
	}

	if (strtod_lower(cursor[0]) == 'n' && strtod_lower(cursor[1]) == 'a' && strtod_lower(cursor[2]) == 'n')
	{
		const char *end_cursor = cursor + 3;
		long double quiet_nan = __builtin_nanl("");

		if (*end_cursor == '(')
		{
			const char *close = end_cursor + 1;

			while (*close != '\0' && *close != ')')
			{
				close++;
			}

			if (*close == ')')
			{
				end_cursor = close + 1;
			}
		}

		if (endptr)
		{
			*endptr = (char *)end_cursor;
		}

		return state.negative ? -quiet_nan : quiet_nan;
	}

	if (cursor[0] == '0' && strtod_lower(cursor[1]) == 'x')
	{
		int hex0;
		int hex1;

		if (strtod_hex_value(cursor[2], &hex0) || (cursor[2] == '.' && strtod_hex_value(cursor[3], &hex1)))
		{
			is_hex = 1;
			digit_base = 16ULL;
			unit = 2.0L;
			chunk_factor = (long double)(1ULL << STRTOD_POW2_CHUNK);
			chunk_power = STRTOD_POW2_CHUNK;
			exponent_limit = STRTOD_HEX_EXPONENT_LIMIT;
			mantissa_cap = STRTOD_HEX_MANTISSA_CAP;

			cursor += 2;
		}
		else
		{
			cursor++;

			if (endptr)
			{
				*endptr = (char *)cursor;
			}

			return state.negative ? -0.0L : 0.0L;
		}
	}

	for (;;)
	{
		int digit_value = -1;

		if (!saw_point && *cursor == '.')
		{
			saw_point = 1;
			cursor++;

			continue;
		}

		if (is_hex)
		{
			if (!strtod_hex_value(*cursor, &digit_value))
			{
				break;
			}
		}
		else
		{
			if (!isdigit((unsigned char)*cursor))
			{
				break;
			}

			digit_value = *cursor - '0';
		}

		saw_digit = 1;

		if (saw_point)
		{
			state.frac_seen++;
		}
		else
		{
			state.integer_digits++;
		}

		if (digit_value != 0 || state.mantissa != 0)
		{
			if (!started)
			{
				state.start_index = state.integer_digits + state.frac_seen;
				started = 1;
			}

			if (state.mantissa <= mantissa_cap)
			{
				state.mantissa = state.mantissa * digit_base + (unsigned long long)digit_value;
				state.absorbed++;
			}
		}

		cursor++;
	}

	if (!saw_digit)
	{
		return 0.0L;
	}

	const char *exponent_cursor = cursor;
	long long user_exponent = 0;
	long long consumed = 0;
	int is_exponent = (is_hex == 0) ? (cursor[0] == 'e' || cursor[0] == 'E') : (cursor[0] == 'p' || cursor[0] == 'P');

	if (is_exponent)
	{
		consumed = strtod_parse_exponent(cursor + 1, &user_exponent);

		if (consumed > 0)
		{
			state.exponent = user_exponent;
			cursor = exponent_cursor + 1 + consumed;
		}
	}

	if (endptr)
	{
		*endptr = (char *)cursor;
	}

	long long positional = state.integer_digits - (state.start_index + state.absorbed - 1);

	if (is_hex)
	{
		positional *= 4;
	}

	positional += state.exponent;

	result = (long double)state.mantissa;

	if (result != 0.0L)
	{
		if (positional > exponent_limit)
		{
			errno = ERANGE;

			return state.negative ? -__builtin_infl() : __builtin_infl();
		}

		if (positional < -exponent_limit)
		{
			errno = ERANGE;

			return state.negative ? -0.0L : 0.0L;
		}

		strtod_scale(&result, positional, chunk_factor, chunk_power, unit, &overflowed, &underflowed);

		if (overflowed)
		{
			result = __builtin_infl();
			errno = ERANGE;
		}
		else if (underflowed)
		{
			result = 0.0L;
			errno = ERANGE;
		}

		if (state.negative)
		{
			result = -result;
		}
	}
	else if (state.negative)
	{
		result = -0.0L;
	}

	return result;
}

static int strtod_special_literal(const char *nptr)
{
	const char *cursor = nptr;
	int first;

	while (isspace((unsigned char)*cursor))
	{
		cursor++;
	}

	if (*cursor == '+' || *cursor == '-')
	{
		cursor++;
	}

	first = strtod_lower((unsigned char)*cursor);

	return first == 'i' || first == 'n';
}

double strtod(const char *nptr, char **endptr)
{
	long double wide = strtold(nptr, endptr);
	double result = (double)wide;

	if (wide > DBL_MAX || wide < -DBL_MAX)
	{
		if (!strtod_special_literal(nptr))
		{
			errno = ERANGE;
		}
	}
	else if (result == 0.0 && wide != 0.0L)
	{
		errno = ERANGE;
	}

	return result;
}

float strtof(const char *nptr, char **endptr)
{
	long double wide = strtold(nptr, endptr);
	float result = (float)wide;

	if (wide > FLT_MAX || wide < -FLT_MAX)
	{
		if (!strtod_special_literal(nptr))
		{
			errno = ERANGE;
		}
	}
	else if (result == 0.0f && wide != 0.0L)
	{
		errno = ERANGE;
	}

	return result;
}

double atof(const char *str)
{
	return strtod(str, (char **)NULL);
}
