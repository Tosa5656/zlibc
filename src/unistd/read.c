#include <unistd.h>
#include "syscall.h"

ssize_t read(int fd, void *buf, size_t count)
{
	return __syscall3(SYSCALL_READ, fd, (long)buf, (long)count);
}
