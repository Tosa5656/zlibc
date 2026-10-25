#include <stdlib.h>

static unsigned long long rand_state = 1ULL;

void srand(unsigned int seed)
{
	rand_state = (unsigned long long)seed;
}

int rand(void)
{
	rand_state = rand_state * 6364136223846793005ULL + 1ULL;

	return (int)((rand_state >> 33) & (unsigned long long)RAND_MAX);
}
