#include "../internal/stdio_impl.h"
#include <stdlib.h>
#include <errno.h>
#include <errors.h>
#include <fcntl.h>
#include <string.h>

FILE *__fdopen(int fd, const char *mode)
{
	FILE *f;

	if (!strchr("rwa", *mode))
	{
		errno = EINVAL;

		return 0;
	}

	f = malloc(sizeof *f + UNGET + BUFSIZ);

	if (!f)
	{
		return 0;
	}

	memset(f, 0, sizeof *f);

	if (!strchr(mode, '+'))
	{
		f->flags = (*mode == 'r') ? F_NOWR : F_NORD;
	}

	if (strchr(mode, 'e'))
	{
		__syscall(SYSCALL_FCNTL, fd, F_SETFD, FD_CLOEXEC);
	}

	if (*mode == 'a')
	{
		f->flags |= F_APP;
	}

	f->fd = fd;
	f->buf = (unsigned char *)f + sizeof *f + UNGET;
	f->buf_size = BUFSIZ;
	f->lbf = EOF;
	f->read = __stdio_read;
	f->write = __stdio_write;
	f->seek = __stdio_seek;
	f->close = __stdio_close;
	f->lock = -1;

	return __ofl_add(f);
}
