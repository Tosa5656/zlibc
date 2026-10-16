#include <ctype.h>

int tolower(int target_char)
{
	if (isupper(target_char))
	{
		return target_char + 32;
	}
	return target_char;
}
