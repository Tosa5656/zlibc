#include <string.h>

char *strtok(char *__restrict string_ptr, const char *__restrict delimiter_chars)
{
	static char *last_token_pos = NULL;

	if (string_ptr == NULL)
	{
		string_ptr = last_token_pos;
		if (string_ptr == NULL)
		{
			return NULL;
		}
	}

	string_ptr += strspn(string_ptr, delimiter_chars);
	if (*string_ptr == '\0')
	{
		last_token_pos = NULL;
		return NULL;
	}

	char *token_end = string_ptr + strcspn(string_ptr, delimiter_chars);
	if (*token_end == '\0')
	{
		last_token_pos = NULL;
	}
	else
	{
		*token_end = '\0';
		last_token_pos = token_end + 1;
	}

	return string_ptr;
}
