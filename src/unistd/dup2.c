#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include "syscall.h"

int dup2(int oldfd, int newfd)
{
	if (oldfd == newfd)
	{
		return oldfd;
	}

	int ret = (int)__syscall3(SYSCALL_FCNTL, oldfd, F_DUPFD, newfd);

	if (ret == -1)
	{
		return -1;
	}

	if (ret != newfd)
	{
		__syscall1(SYSCALL_CLOSE, ret);
		return -1;
	}

	return ret;
}
