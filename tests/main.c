#include "ctype/test.h"
#include "errno/test.h"
#include "stdio/test.h"
#include "string/test.h"

int main(void)
{
	test_errno();
	test_ctype();
	test_string();
	test_stdio();

	test_finish();
	test_summary();

	return test_failures;
}
