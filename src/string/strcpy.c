#include <string.h>

char *strcpy(char *__restrict destination_str, const char *__restrict source_str)
{
	size_t index = 0;

	while (source_str[index] != '\0')
	{
		destination_str[index] = source_str[index];
		index++;
	}

	destination_str[index] = '\0';

	return destination_str;
}
