#include "../internal/stdio_impl.h"

FILE **__ofl_lock(void);

static FILE *ofl_head;

FILE **__ofl_lock(void)
{
	/* TODO: if multithreading write fully function */
	return &ofl_head;
}
