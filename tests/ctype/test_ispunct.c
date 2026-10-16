#include "test.h"

void test_ispunct(void)
{
	/* Printable characters that are neither alphanumeric nor a space. */
	static const int ranges[] = { '!', '/', ':', '@', '[', '`', '{', '~' };

	test_suite("ispunct");

	test_ctype_class("ispunct", ispunct, ranges, 4);

	CHECK(ispunct('!'));
	CHECK(ispunct('/'));
	CHECK(ispunct(':'));
	CHECK(ispunct('@'));
	CHECK(ispunct('['));
	CHECK(ispunct('`'));
	CHECK(ispunct('{'));
	CHECK(ispunct('~'));

	CHECK(!ispunct(' '));
	CHECK(!ispunct('0'));
	CHECK(!ispunct('9'));
	CHECK(!ispunct('A'));
	CHECK(!ispunct('Z'));
	CHECK(!ispunct('a'));
	CHECK(!ispunct('z'));
	CHECK(!ispunct('\t'));
	CHECK(!ispunct('\0'));
	CHECK(!ispunct(127));
}
