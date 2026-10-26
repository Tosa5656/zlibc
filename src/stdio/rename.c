#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <errors.h>
#include <errors.h>
#include <stdlib.h>
#include <string.h>
#include "syscall.h"

#define SYSCALL_RENAME 82

int rename(const char *old, const char *new)
{
	long r = __syscall(SYSCALL_RENAME, (long)old, (long)new);

	if (r >= 0)
	{
		return 0;
	}

	{
		long src = __syscall(SYSCALL_OPEN, (long)old, O_RDONLY, 0);
		long dst;
		unsigned char chunk[4096];
		long got;
		long put;

		if (src < 0)
		{
			__syscall_ret(r);

			return -1;
		}

		dst = __syscall(SYSCALL_OPEN, (long)new, O_WRONLY|O_CREAT|O_TRUNC, 0666);

		if (dst < 0)
		{
			__syscall_ret(__syscall(SYSCALL_CLOSE, src));

			return -1;
		}

		while ((got = __syscall(SYSCALL_READ, src, (long)chunk, sizeof chunk)) > 0)
		{
			long wrote = 0;

			while (wrote < got)
			{
				put = __syscall(SYSCALL_WRITE, dst, (long)((unsigned char *)chunk + wrote), got - wrote);

				if (put <= 0)
				{
					goto copy_failed;
				}

				wrote += put;
			}
		}

		if (got < 0)
		{
			goto copy_failed;
		}

		__syscall_ret(__syscall(SYSCALL_CLOSE, dst));
		r = __syscall(SYSCALL_UNLINK, (long)old);
		__syscall_ret(__syscall(SYSCALL_CLOSE, src));

		return __syscall_ret(r) < 0 ? -1 : 0;

copy_failed:
		__syscall_ret(__syscall(SYSCALL_CLOSE, dst));
		__syscall_ret(__syscall(SYSCALL_CLOSE, src));

		return -1;
	}
}
