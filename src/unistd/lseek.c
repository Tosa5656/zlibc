#include <unistd.h>
#include <errno.h>
#include "syscall.h"

off_t lseek(int fd, off_t offset, int whence)
{
	long ret = __syscall3(SYSCALL_SEEK, fd, offset, whence);

	if (ret < 0)
	{
		errno = -ret;
		return -1;
	}

	return ret;
}
