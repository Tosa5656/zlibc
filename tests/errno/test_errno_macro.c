#include "test.h"

void test_errno_macro(void)
{
	int saved;

	test_suite("errno");

	CHECK_INT(errno, 0);

	errno = 0;
	CHECK_INT(errno, 0);

	errno = ENOENT;
	CHECK_INT(errno, ENOENT);

	errno = EHWPOISON;
	CHECK_INT(errno, EHWPOISON);

	errno = ERANGE - 1;
	errno++;
	CHECK_INT(errno, ERANGE);

	errno = 0;
	errno += EINTR;
	CHECK_INT(errno, EINTR);

	errno = -1;
	CHECK_INT(errno, -1);

	errno = INT_MAX;
	CHECK_INT(errno, INT_MAX);

	errno = INT_MIN;
	CHECK_INT(errno, INT_MIN);

	saved = 42;
	errno = EIO;
	CHECK_INT(saved, 42);
	CHECK_INT(errno, EIO);

	saved = errno;
	errno = EAGAIN;
	errno = saved;
	CHECK_INT(errno, EIO);

	errno = 0;
}
