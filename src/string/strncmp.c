#include <string.h>

int strncmp(const char *string1, const char *string2, size_t max_num_chars)
{
	size_t i = 0;

	if (max_num_chars == 0)
	{
		return 0;
	}

	while (i < max_num_chars - 1 && string1[i] != '\0' && string1[i] == string2[i])
	{
		i++;
	}

	unsigned char left = (unsigned char)string1[i];
	unsigned char right = (unsigned char)string2[i];

	return (left < right) ? -1 : (left > right);
}
