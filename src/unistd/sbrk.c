#include <unistd.h>
#include <errno.h>
#include "syscall.h"

int brk(void *addr)
{
	unsigned long ret = __syscall1(SYSCALL_BRK, (long)addr);

	if (ret == (unsigned long)-1)
	{
		errno = ENOMEM;
		return -1;
	}

	return 0;
}

void *sbrk(intptr_t increment)
{
	unsigned long old = __syscall1(SYSCALL_BRK, 0);

	if (old == (unsigned long)-1)
	{
		errno = ENOMEM;
		return (void *)-1;
	}

	if (increment == 0)
	{
		return (void *)old;
	}

	unsigned long ret = __syscall1(SYSCALL_BRK, (long)(old + increment));

	if (ret == (unsigned long)-1)
	{
		errno = ENOMEM;
		return (void *)-1;
	}

	return (void *)old;
}
