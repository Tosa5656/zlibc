#include <string.h>

size_t strspn(const char *string_ptr, const char *accepted_chars)
{
	size_t count = 0;

	while (string_ptr[count] != '\0')
	{
		size_t i = 0;
		int found = 0;

		while (accepted_chars[i] != '\0')
		{
			if (string_ptr[count] == accepted_chars[i])
			{
				found = 1;
				break;
			}
			i++;
		}

		if (!found)
		{
			return count;
		}

		count++;
	}

	return count;
}
