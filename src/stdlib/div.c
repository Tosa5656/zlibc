#include <stdlib.h>

#define INT_MIN_LOCAL	(-1 - 0x7fffffff)
#define LONG_MAX_LOCAL	(8 == sizeof(long) ? 0x7fffffffffffffffL : 0x7fffffffL)
#define LONG_MIN_LOCAL	(-1L - LONG_MAX_LOCAL)
#define LLONG_MIN_LOCAL	(-1LL - 0x7fffffffffffffffLL)

div_t div(int numer, int denom)
{
	div_t result;

	if (denom == 0)
	{
		result.quot = 0;
		result.rem = 0;

		return result;
	}

	if (numer == INT_MIN_LOCAL && denom == -1)
	{
		result.quot = numer;
		result.rem = 0;

		return result;
	}

	result.quot = numer / denom;
	result.rem = numer % denom;

	return result;
}

ldiv_t ldiv(long numer, long denom)
{
	ldiv_t result;

	if (denom == 0)
	{
		return result;
	}

	if (numer == LONG_MIN_LOCAL && denom == -1)
	{
		result.quot = numer;
		result.rem = 0;

		return result;
	}

	result.quot = numer / denom;
	result.rem = numer % denom;

	return result;
}

lldiv_t lldiv(long long numer, long long denom)
{
	lldiv_t result;

	if (denom == 0)
	{
		return result;
	}

	if (numer == LLONG_MIN_LOCAL && denom == -1)
	{
		result.quot = numer;
		result.rem = 0;

		return result;
	}

	result.quot = numer / denom;
	result.rem = numer % denom;

	return result;
}
