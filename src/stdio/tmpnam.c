#include "../internal/stdio_impl.h"
#include <fcntl.h>
#include <string.h>

#define MAXTRIES 100

char *tmpnam(char *buf)
{
	static char internal[L_tmpnam];
	char s[] = "tmpnam_XXXXXX";
	int try;

	for (try = 0; try < MAXTRIES; try++)
	{
		__randname(s+7);

		if (__syscall(SYSCALL_OPEN, (long)s, O_RDWR, 0) < 0)
		{
			return strcpy(buf ? buf : internal, s);
		}
	}

	return 0;
}
