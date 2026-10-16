#include <ctype.h>

int isprint(int target_char)
{
	return (target_char >= 32 && target_char <= 126);
}
