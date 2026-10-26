#include <unistd.h>
#include "syscall.h"

pid_t getpid(void)
{
	return __syscall0(SYSCALL_GETPID);
}

pid_t getppid(void)
{
	return __syscall0(SYSCALL_GETPPID);
}

pid_t getpgrp(void)
{
	return getpid();
}
