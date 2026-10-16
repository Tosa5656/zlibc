#include <ctype.h>

int isalpha(int target_char)
{
	return (islower(target_char) || isupper(target_char));
}
