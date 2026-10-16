#include <string.h>

size_t strlen(const char *string_ptr)
{
	size_t length = 0;

	while (string_ptr[length] != '\0')
	{
		length++;
	}

	return length;
}
