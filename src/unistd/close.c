#include <unistd.h>
#include "syscall.h"

int close(int fd)
{
	return (int)__syscall1(SYSCALL_CLOSE, fd);
}
