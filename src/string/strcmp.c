#include <string.h>

int strcmp(const char *string1, const char *string2)
{
	size_t i = 0;

	while (string1[i] != '\0' && string1[i] == string2[i])
	{
		i++;
	}

	unsigned char left = (unsigned char)string1[i];
	unsigned char right = (unsigned char)string2[i];

	return (left < right) ? -1 : (left > right);
}
