#include <ctype.h>

int ispunct(int target_char)
{
	return (isprint(target_char) && !isalnum(target_char) && !isspace(target_char));
}
