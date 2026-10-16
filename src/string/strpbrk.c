#include <string.h>

char *strpbrk(const char *string_ptr, const char *accepted_chars)
{
	while (*string_ptr != '\0')
	{
		size_t i = 0;
		while (accepted_chars[i] != '\0')
		{
			if (*string_ptr == accepted_chars[i])
			{
				return (char *)string_ptr;
			}
			i++;
		}
		string_ptr++;
	}

	return NULL;
}
