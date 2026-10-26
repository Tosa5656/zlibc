#include "../internal/stdio_impl.h"
#include <fcntl.h>
#include <stdlib.h>

#define MAXTRIES 100

FILE *tmpfile(void)
{
	char s[] = "tmpfile_XXXXXX";
	int fd;
	FILE *f;
	int try;

	for (try = 0; try < MAXTRIES; try++)
	{
		__randname(s+8);

		fd = __syscall(SYSCALL_OPEN, (long)s, O_RDWR|O_CREAT|O_EXCL, 0600);

		if (fd >= 0)
		{
			__syscall(SYSCALL_UNLINK, (long)s);

			f = __fdopen(fd, "w+");

			if (!f)
			{
				__syscall(SYSCALL_CLOSE, fd);
			}

			return f;
		}
	}

	return 0;
}
