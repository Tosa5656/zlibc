#include <stdio.h>
#include <stdarg.h>

int vscanf(const char *__restrict fmt, va_list ap)
{
	return vfscanf(stdin, fmt, ap);
}

int scanf(const char *__restrict fmt, ...)
{
	int ret;
	va_list ap;

	va_start(ap, fmt);
	ret = vfscanf(stdin, fmt, ap);
	va_end(ap);

	return ret;
}

int fscanf(FILE *__restrict f, const char *__restrict fmt, ...)
{
	int ret;
	va_list ap;

	va_start(ap, fmt);
	ret = vfscanf(f, fmt, ap);
	va_end(ap);

	return ret;
}
