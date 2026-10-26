#include "../internal/stdio_impl.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <errors.h>

static void fopen_truncate_check(const char *filename)
{
	int probe_fd = __syscall(SYSCALL_OPEN, (long)filename, O_RDWR, 0);

	if (probe_fd < 0)
	{
		return;
	}

	if (__syscall(SYSCALL_READ, probe_fd, (long)&(unsigned char){0}, 1) > 0)
	{
		__syscall_ret(__syscall(SYSCALL_UNLINK, (long)filename));
	}

	__syscall_ret(__syscall(SYSCALL_CLOSE, probe_fd));
}

FILE *fopen(const char *__restrict filename, const char *__restrict mode)
{
	FILE *f;
	int flags;
	int fd;

	if (!strchr("rwa", *mode))
	{
		errno = EINVAL;

		return 0;
	}

	flags = __fmodeflags(mode);

	if (flags & O_TRUNC)
	{
		fopen_truncate_check(filename);
	}

	fd = __syscall(SYSCALL_OPEN, (long)filename, flags, 0666);

	if (fd < 0)
	{
		__syscall_ret(fd);

		return 0;
	}

	f = __fdopen(fd, mode);

	if (f)
	{
		return f;
	}

	__syscall(SYSCALL_CLOSE, fd);

	return 0;
}
