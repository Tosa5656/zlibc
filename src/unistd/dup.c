#include <unistd.h>
#include "syscall.h"

int dup(int fd)
{
	return (int)__syscall1(SYSCALL_DUP, fd);
}
