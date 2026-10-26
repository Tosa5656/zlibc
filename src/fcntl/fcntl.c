#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include <errors.h>
#include <syscall.h>

int fcntl(int fd, int cmd, ...)
{
	unsigned long arg;
	va_list ap;
	va_start(ap, cmd);
	arg = va_arg(ap, unsigned long);
	va_end(ap);
	if (cmd == F_SETFL) arg |= O_LARGEFILE;
	if (cmd == F_SETLKW) return syscall_cp(SYSCALL_FCNTL, fd, cmd, (long)arg);
	if (cmd == F_GETOWN)
	{
		struct f_owner_ex ex;
		int ret = __syscall(SYSCALL_FCNTL, fd, F_GETOWN_EX, (long)&ex);
		if (ret == -EINVAL) return __syscall(SYSCALL_FCNTL, fd, cmd, (long)arg);
		if (ret) return __syscall_ret(ret);
		return ex.type == F_OWNER_PGRP ? -ex.pid : ex.pid;
	}
	if (cmd == F_DUPFD_CLOEXEC)
	{
		int ret = __syscall(SYSCALL_FCNTL, fd, F_DUPFD_CLOEXEC, arg);
		if(ret != -EINVAL)
		{
			if(ret >= 0)
				__syscall(SYSCALL_FCNTL, ret, F_SETFD, FD_CLOEXEC);
			return __syscall_ret(ret);
		}
		ret = __syscall3(SYSCALL_FCNTL, fd, F_DUPFD_CLOEXEC, 0);
		if (ret != -EINVAL)
		{
			if (ret >= 0) __syscall(SYSCALL_CLOSE, ret);
			return __syscall_ret(-EINVAL);
		}
		ret = __syscall3(SYSCALL_FCNTL, fd, F_DUPFD, arg);
		if (ret >= 0) __syscall(SYSCALL_FCNTL, ret, F_SETFD, FD_CLOEXEC);
		return __syscall_ret(ret);
	}

	switch (cmd)
	{
	case F_SETLK:
	case F_GETLK:
	case F_GETOWN_EX:
	case F_SETOWN_EX:
		return __syscall(SYSCALL_FCNTL, fd, cmd, (long)arg);
	default:
		return __syscall(SYSCALL_FCNTL, fd, cmd, arg);
	}
}
