#include <ctype.h>

int toupper(int target_char)
{
	if (islower(target_char))
	{
		return target_char - 32;
	}
	return target_char;
}
