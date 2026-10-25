#include <stdlib.h>
#include <errno.h>
#include <errors.h>

size_t __ctype_get_mb_cur_max(void)
{
	return 1;
}

int mblen(const char *string, size_t max_bytes)
{
	if (string == NULL)
	{
		return 0;
	}

	if (max_bytes == 0)
	{
		return -1;
	}

	if (*string == '\0')
	{
		return 0;
	}

	return 1;
}

int mbtowc(wchar_t *wide_out, const char *string, size_t max_bytes)
{
	if (string == NULL)
	{
		return 0;
	}

	if (max_bytes == 0)
	{
		return -1;
	}

	if (*string == '\0')
	{
		if (wide_out != NULL)
		{
			*wide_out = 0;
		}

		return 0;
	}

	if (wide_out != NULL)
	{
		*wide_out = (wchar_t)(unsigned char)*string;
	}

	return 1;
}

int wctomb(char *string, wchar_t wide)
{
	if (string == NULL)
	{
		return 0;
	}

	if ((unsigned char)wide != wide)
	{
		errno = EILSEQ;

		return -1;
	}

	*string = (char)(unsigned char)wide;

	return 1;
}

size_t mbstowcs(wchar_t *wide_out, const char *string, size_t wide_max)
{
	size_t index = 0;

	if (string == NULL)
	{
		return (size_t)-1;
	}

	if (wide_out == NULL)
	{
		while (string[index] != '\0')
		{
			index++;
		}

		return index;
	}

	while (index < wide_max && string[index] != '\0')
	{
		wide_out[index] = (wchar_t)(unsigned char)string[index];
		index++;
	}

	if (index < wide_max)
	{
		wide_out[index] = 0;
	}

	return index;
}

size_t wcstombs(char *string_out, const wchar_t *wide, size_t string_max)
{
	size_t index = 0;

	if (wide == NULL)
	{
		return (size_t)-1;
	}

	if (string_out == NULL)
	{
		while (wide[index] != 0)
		{
			if ((unsigned char)wide[index] != wide[index])
			{
				return (size_t)-1;
			}

			index++;
		}

		return index;
	}

	while (index < string_max)
	{
		if ((unsigned char)wide[index] != wide[index])
		{
			return (size_t)-1;
		}

		string_out[index] = (char)(unsigned char)wide[index];

		if (wide[index] == 0)
		{
			return index;
		}

		index++;
	}

	return index;
}
