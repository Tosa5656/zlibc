#include <string.h>

char *strchr(const char *string_ptr, int target_char)
{
	char value = (char)target_char;

	while (*string_ptr != '\0')
	{
		if (*string_ptr == value)
		{
			return (char *)string_ptr;
		}
		string_ptr++;
	}

	if (value == '\0')
	{
		return (char *)string_ptr;
	}

	return NULL;
}
