#include <unistd.h>
#include "syscall.h"

_Noreturn void _exit(int status)
{
	for (;;) __syscall1(SYSCALL_EXIT, status);
}
