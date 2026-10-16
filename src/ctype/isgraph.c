#include <ctype.h>

int isgraph(int target_char)
{
	return (target_char >= 33 && target_char <= 126);
}
