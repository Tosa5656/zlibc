#include <unistd.h>

int isatty(int fd)
{
	(void)fd;
	/* Пока единственный stdout/stdin — консоль. */
	return 1;
}
