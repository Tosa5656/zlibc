#include "../internal/stdio_impl.h"

int __stdio_close(FILE *f)
{
	return __syscall_ret(__syscall(SYSCALL_CLOSE, f->fd));
}
