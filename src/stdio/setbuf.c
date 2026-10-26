#include <stdio.h>

void setbuf(FILE *__restrict f, char *__restrict buf)
{
	setvbuf(f, buf, buf ? _IOFBF : _IONBF, BUFSIZ);
}
