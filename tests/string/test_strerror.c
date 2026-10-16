#include "test.h"

void test_strerror(void)
{
	test_suite("strerror");

	CHECK_STR(strerror(0), "Success");
	CHECK_STR(strerror(2), "No such file or directory");
	CHECK_STR(strerror(13), "Permission denied");
	CHECK_STR(strerror(22), "Invalid argument");
	CHECK_STR(strerror(111), "Connection refused");
	CHECK_STR(strerror(134), "Not supported");

	CHECK_STR(strerror(47), "Unknown error");
	CHECK_STR(strerror(-1), "Unknown error");
	CHECK_STR(strerror(9999), "Unknown error");
}
