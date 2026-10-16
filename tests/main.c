#include "ctype/test.h"
#include "string/test.h"

int main(void)
{
	test_ctype();
	test_string();

	test_finish();
	test_summary();

	return test_failures;
}
