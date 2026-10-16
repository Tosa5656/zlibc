#include <ctype.h>

int isalnum(int target_char)
{
	return (isalpha(target_char) || isdigit(target_char));
}
