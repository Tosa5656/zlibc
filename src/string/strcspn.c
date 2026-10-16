#include <string.h>

size_t strcspn(const char *string_ptr, const char *rejected_chars)
{
	size_t count = 0;

	while (string_ptr[count] != '\0')
	{
		size_t i = 0;
		while (rejected_chars[i] != '\0')
		{
			if (string_ptr[count] == rejected_chars[i])
			{
				return count;
			}
			i++;
		}
		count++;
	}

	return count;
}
