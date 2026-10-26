#include <stdio.h>
#include <errno.h>
#include <errors.h>
#include <errors.h>
#include <fcntl.h>
#include "syscall.h"

int remove(const char *path)
{
	long r = __syscall(SYSCALL_UNLINK, (long)path);

	if (r == -EISDIR)
	{
		r = __syscall(SYSCALL_RMDIR, (long)path);
	}

	return __syscall_ret(r);
}
