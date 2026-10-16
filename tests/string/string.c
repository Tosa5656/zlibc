#include "test.h"

void test_string(void)
{
	test_memcpy();
	test_memmove();
	test_memset();
	test_memcmp();
	test_memchr();

	test_strcpy();
	test_strncpy();
	test_strcat();
	test_strncat();

	test_strcmp();
	test_strncmp();
	test_strcoll();
	test_strxfrm();

	test_strchr();
	test_strrchr();
	test_strspn();
	test_strcspn();
	test_strpbrk();
	test_strstr();

	test_strlen();
	test_strtok();
	test_strerror();
}
