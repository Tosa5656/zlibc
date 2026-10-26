#include "../internal/stdio_impl.h"
#include <stdlib.h>

int fputc(int c, FILE *f)
{
	int r;

	f->mode |= f->mode-1;
	__stdio_exit_needed();

	if (f->wpos < f->wend && c != f->lbf)
	{
		r = *f->wpos++ = c;
	}
	else
	{
		r = __overflow(f, c);
	}

	return r;
}

int putc(int c, FILE *f)
{
	return fputc(c, f);
}

int putchar(int c)
{
	return fputc(c, stdout);
}
