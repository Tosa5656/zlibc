#include <unistd.h>
#include <alltypes.h>
#include <errno.h>
#include "syscall.h"

int nanosleep(const struct timespec *req, struct timespec *rem)
{
	(void)rem;
	return (int)__syscall1(SYSCALL_NAONSLEEP, (long)req);
}

unsigned sleep(unsigned seconds)
{
	struct timespec req = { .tv_sec = (long)seconds, .tv_nsec = 0 };

	if (__syscall1(SYSCALL_NAONSLEEP, (long)&req) < 0)
	{
		return seconds;
	}

	return 0;
}

int usleep(unsigned usec)
{
	struct timespec req =
	{
		.tv_sec = usec / 1000000,
		.tv_nsec = (usec % 1000000) * 1000
	};

	return (int)__syscall1(SYSCALL_NAONSLEEP, (long)&req);
}
