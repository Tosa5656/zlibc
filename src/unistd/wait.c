#include <sys/wait.h>
#include "syscall.h"

pid_t waitpid(pid_t pid, int *status, int options)
{
	long ret = __syscall3(SYSCALL_WAITPID, pid, (long)status, options);

	if (ret < 0)
	{
		return -1;
	}

	return (pid_t)ret;
}

pid_t wait(int *status)
{
	return waitpid(-1, status, 0);
}
