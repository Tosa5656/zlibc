#include "../internal/stdio_impl.h"
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

static void freopen_detach(FILE *f2)
{
	FILE **head = __ofl_lock();

	if (f2->prev)
	{
		f2->prev->next = f2->next;
	}

	if (f2->next)
	{
		f2->next->prev = f2->prev;
	}

	if (*head == f2)
	{
		*head = f2->next;
	}

	free(f2);
}

FILE *freopen(const char *__restrict filename, const char *__restrict mode, FILE *__restrict f)
{
	FILE *f2;

	fflush(f);

	if (!filename)
	{
		__syscall(SYSCALL_FCNTL, f->fd, F_SETFL, __fmodeflags(mode) & ~(O_CREAT|O_EXCL|O_CLOEXEC));
		f->mode = 0;

		return f;
	}

	__syscall_ret(__syscall(SYSCALL_CLOSE, f->fd));

	f2 = fopen(filename, mode);

	if (!f2)
	{
		fclose(f);

		return 0;
	}

	f->flags = (f->flags & F_PERM) | f2->flags;
	f->read = f2->read;
	f->write = f2->write;
	f->seek = f2->seek;
	f->close = f2->close;
	f->fd = f2->fd;

	freopen_detach(f2);

	f->mode = 0;

	return f;
}
