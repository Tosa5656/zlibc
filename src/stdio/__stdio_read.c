#include "../internal/stdio_impl.h"
#include <string.h>

size_t __stdio_read(FILE *f, unsigned char *buf, size_t len)
{
	size_t take;

	if (f->buf_size)
	{
		long cnt = __syscall(SYSCALL_READ, f->fd, (long)f->buf, (long)f->buf_size);

		if (cnt <= 0)
		{
			f->flags |= cnt ? F_ERR : F_EOF;

			return 0;
		}

		take = (size_t)cnt < len ? (size_t)cnt : len;

		memcpy(buf, f->buf, take);
		f->rpos = f->buf + take;
		f->rend = f->buf + cnt;

		return take;
	}

	{
		long cnt = __syscall(SYSCALL_READ, f->fd, (long)buf, (long)len);

		if (cnt <= 0)
		{
			f->flags |= cnt ? F_ERR : F_EOF;

			return 0;
		}

		return cnt;
	}
}
