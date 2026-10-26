#include "../internal/stdio_impl.h"

off_t __stdio_seek(FILE *f, off_t off, int whence)
{
	return __syscall_ret(__syscall(SYSCALL_SEEK, f->fd, off, whence));
}
