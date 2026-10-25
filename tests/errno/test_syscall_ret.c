#include "test.h"

#include "../../include/sys/syscall.h"

void test_syscall_ret(void)
{
	test_suite("__syscall_ret");

	errno = 0;
	CHECK_INT(__syscall_ret(0), 0);
	CHECK_INT(errno, 0);

	errno = EIO;
	CHECK_INT(__syscall_ret(1), 1);
	CHECK_INT(errno, EIO);

	errno = EIO;
	CHECK_INT(__syscall_ret(4096), 4096);
	CHECK_INT(errno, EIO);

	errno = EIO;
	CHECK_INT(__syscall_ret((unsigned long)-4096), -4096);
	CHECK_INT(errno, EIO);

	errno = 0;
	CHECK_INT(__syscall_ret((unsigned long)-EPERM), -1);
	CHECK_INT(errno, EPERM);

	errno = 0;
	CHECK_INT(__syscall_ret((unsigned long)-ENOENT), -1);
	CHECK_INT(errno, ENOENT);

	errno = 0;
	CHECK_INT(__syscall_ret((unsigned long)-4095), -1);
	CHECK_INT(errno, 4095);

	errno = 0;
	CHECK_INT(__syscall_ret((unsigned long)-1), -1);
	CHECK_INT(errno, 1);

	errno = 0;
}
