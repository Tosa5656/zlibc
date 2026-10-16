#include <ctype.h>

int isxdigit(int target_char)
{
	return (isdigit(target_char) || (target_char >= 'a' && target_char <= 'f') || (target_char >= 'A' && target_char <= 'F'));
}
