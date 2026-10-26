#include "../internal/stdio_impl.h"
#include <stdlib.h>

static const char randname_chars[] = "abcdefghijklmnopqrstuvwxyz1234567890";

void __randname(char *buf)
{
	static unsigned seed;
	int i;

	for (i = 0; i < 6; i++)
	{
		seed = seed*6364136223846793005ULL + rand();
		buf[i] = randname_chars[(seed >> 10) % (sizeof randname_chars - 1)];
	}

	buf[6] = 0;
}
