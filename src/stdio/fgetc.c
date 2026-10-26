#include "../internal/stdio_impl.h"
#include <stdlib.h>

int fgetc(FILE *f)
{
	int c;

	f->mode |= f->mode-1;
	__stdio_exit_needed();

	if (f->rpos < f->rend)
	{
		c = *f->rpos++;
	}
	else
	{
		c = __uflow(f);
	}

	return c;
}

int getc(FILE *f)
{
	return fgetc(f);
}

int getchar(void)
{
	return fgetc(stdin);
}
