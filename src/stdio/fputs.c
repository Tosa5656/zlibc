#include "../internal/stdio_impl.h"
#include <string.h>

int fputs(const char *__restrict s, FILE *__restrict f)
{
	size_t l = strlen(s);

	return (fwrite(s, 1, l, f) == l) - 1;
}
