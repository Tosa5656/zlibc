#include "test.h"

void test_errno_location(void)
{
	int *location;
	int index;

	test_suite("__errno_location");

	location = __errno_location();
	CHECK(location != NULL);
	CHECK_PTR(__errno_location(), location);

	errno = 0;
	CHECK_INT(*location, 0);

	errno = EACCES;
	CHECK_INT(*location, EACCES);

	*location = ENOMEM;
	CHECK_INT(errno, ENOMEM);

	for (index = 0; index < 100; index++)
	{
		errno = index;
		CHECK_PTR(__errno_location(), location);
	}

	errno = 0;
}
