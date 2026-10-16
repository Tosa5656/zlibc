#include <string.h>

char *strcat(char *__restrict destination_str, const char *__restrict source_str)
{
	size_t dest_index = 0;
	size_t src_index = 0;

	while (destination_str[dest_index] != '\0')
	{
		dest_index++;
	}

	while (source_str[src_index] != '\0')
	{
		destination_str[dest_index] = source_str[src_index];
		dest_index++;
		src_index++;
	}

	destination_str[dest_index] = '\0';

	return destination_str;
}
