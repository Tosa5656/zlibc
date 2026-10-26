#include <stdio.h>
#include <stdarg.h>

int sscanf(const char *__restrict s, const char *__restrict fmt, ...)
{
	int ret;
	va_list ap;

	va_start(ap, fmt);
	ret = vsscanf(s, fmt, ap);
	va_end(ap);

	return ret;
}
