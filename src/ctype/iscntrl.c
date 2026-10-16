#include <ctype.h>

int iscntrl(int target_char)
{
	return ((target_char >= 0 && target_char <= 31) || target_char == 127);
}
