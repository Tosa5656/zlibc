#include <string.h>

char *strncpy(char *__restrict destination_str, const char *__restrict source_str, size_t max_num_chars)
{
	size_t i = 0;

	while (i < max_num_chars && source_str[i] != '\0')
	{
		destination_str[i] = source_str[i];
		i++;
	}

	while (i < max_num_chars)
	{
		destination_str[i] = '\0';
		i++;
	}

	return destination_str;
}
