#include <string.h>

// TODO: when strcoll done rewrite function
size_t strxfrm(char *__restrict destination_str, const char *__restrict source_str, size_t max_num_chars)
{
	size_t src_len = strlen(source_str);

	if (max_num_chars > 0 && destination_str != NULL)
	{
		size_t copy_len = (src_len < max_num_chars) ? src_len : max_num_chars - 1;

		for (size_t i = 0; i < copy_len; i++)
		{
			destination_str[i] = source_str[i];
		}

		destination_str[copy_len] = '\0';
	}

	return src_len;
}
