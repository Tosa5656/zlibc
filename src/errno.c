#include <errno.h>

static _Thread_local int __libc_errno = 0;

int *__errno_location(void)
{
    return &__libc_errno;
}