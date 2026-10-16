#include <ctype.h>

int isspace(int target_char)
{
	return (target_char == ' ' || target_char == '\t' || target_char == '\n' || target_char == '\v' || target_char == '\f' || target_char == '\r');
}
