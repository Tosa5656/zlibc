#include <string.h>

char *strstr(const char *haystack_string, const char *needle_string)
{
	if (*needle_string == '\0')
	{
		return (char *)haystack_string;
	}

	while (*haystack_string != '\0')
	{
		const char *h = haystack_string;
		const char *n = needle_string;

		while (*h != '\0' && *n != '\0' && *h == *n)
		{
			h++;
			n++;
		}

		if (*n == '\0')
		{
			return (char *)haystack_string;
		}

		haystack_string++;
	}

	return NULL;
}
