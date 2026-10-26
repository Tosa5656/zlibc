#include "../internal/stdio_impl.h"

int puts(const char *s)
{
	int r;

	FLOCK(stdout);

	r = -(fputs(s, stdout) < 0 || putc('\n', stdout) < 0);

	FUNLOCK(stdout);

	return r;
}
