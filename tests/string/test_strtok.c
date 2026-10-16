#include "test.h"

void test_strtok(void)
{
	char text[] = "  one,,two three ";
	char other[] = "alpha;beta";
	char delimiters[] = ",,,";
	char *token;

	test_suite("strtok");

	token = strtok(text, " ,");
	CHECK(token != NULL && test_streq(token, "one"));

	token = strtok(NULL, " ,");
	CHECK(token != NULL && test_streq(token, "two"));

	token = strtok(NULL, " ,");
	CHECK(token != NULL && test_streq(token, "three"));

	CHECK(strtok(NULL, " ,") == NULL);
	CHECK(strtok(NULL, " ,") == NULL);

	token = strtok(other, ";");
	CHECK(token != NULL && test_streq(token, "alpha"));

	token = strtok(NULL, ";");
	CHECK(token != NULL && test_streq(token, "beta"));

	CHECK(strtok(NULL, ";") == NULL);

	CHECK(strtok(delimiters, ",") == NULL);
}
