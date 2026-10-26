#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

int vprintf(const char *__restrict fmt, va_list ap)
{
	return vfprintf(stdout, fmt, ap);
}

int printf(const char *__restrict fmt, ...)
{
	int ret;
	va_list ap;

	va_start(ap, fmt);
	ret = vfprintf(stdout, fmt, ap);
	va_end(ap);

	return ret;
}

int fprintf(FILE *__restrict f, const char *__restrict fmt, ...)
{
	int ret;
	va_list ap;

	va_start(ap, fmt);
	ret = vfprintf(f, fmt, ap);
	va_end(ap);

	return ret;
}

int vsprintf(char *__restrict s, const char *__restrict fmt, va_list ap)
{
	return vsnprintf(s, INT_MAX, fmt, ap);
}

int sprintf(char *__restrict s, const char *__restrict fmt, ...)
{
	int ret;
	va_list ap;

	va_start(ap, fmt);
	ret = vsnprintf(s, INT_MAX, fmt, ap);
	va_end(ap);

	return ret;
}

int snprintf(char *__restrict s, size_t n, const char *__restrict fmt, ...)
{
	int ret;
	va_list ap;

	va_start(ap, fmt);
	ret = vsnprintf(s, n, fmt, ap);
	va_end(ap);

	return ret;
}
