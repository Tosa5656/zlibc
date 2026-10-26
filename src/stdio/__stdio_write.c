#include "../internal/stdio_impl.h"

size_t __stdio_write(FILE *f, const unsigned char *buf, size_t len)
{
	const unsigned char *first = f->wbase;
	size_t first_len = f->wpos - f->wbase;
	const unsigned char *second = buf;
	size_t second_len = len;
	size_t written = 0;

	if ((f->flags & F_APP) && (first_len || second_len))
	{
		__syscall(SYSCALL_SEEK, f->fd, 0, SEEK_END);
	}

	while (first_len)
	{
		long w = __syscall(SYSCALL_WRITE, f->fd, (long)first, (long)first_len);

		if (w <= 0)
		{
			goto error;
		}

		first += w;
		first_len -= w;
		written += w;
	}

	while (second_len)
	{
		long w = __syscall(SYSCALL_WRITE, f->fd, (long)second, (long)second_len);

		if (w <= 0)
		{
			goto error;
		}

		second += w;
		second_len -= w;
		written += w;
	}

	f->wend = f->buf + f->buf_size;
	f->wpos = f->wbase = f->buf;

	return len;

error:
	f->wpos = f->wbase = f->wend = 0;
	f->flags |= F_ERR;

	return written;
}
