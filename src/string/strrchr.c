#include <string.h>

char *strrchr(const char *string_ptr, int target_char)
{
	char value = (char)target_char;
	const char *last_found = NULL;

	while (*string_ptr != '\0')
	{
		if (*string_ptr == value)
		{
			last_found = string_ptr;
		}
		string_ptr++;
	}

	if (value == '\0')
	{
		return (char *)string_ptr;
	}

	return (char *)last_found;
}
