#include "../internal/stdio_impl.h"
#include <stdlib.h>

static void close_file(FILE *f)
{
	if (!f)
	{
		return;
	}

	if (f->wpos != f->wbase)
	{
		f->write(f, 0, 0);
	}

	if (f->rpos != f->rend)
	{
		f->seek(f, f->rpos-f->rend, SEEK_CUR);
	}
}

void __stdio_exit(void)
{
	FILE **head = __ofl_lock();
	FILE *f;

	for (f = *head; f; f = f->next)
	{
		close_file(f);
	}

	close_file(__stdin_used);
	close_file(__stdout_used);
	close_file(__stderr_used);
}

/*
 * The zlibc exit path has no direct stdio dependency, so the first real
 * stdio use registers the flush as an atexit hook. Registered first, it
 * runs last, after application handlers.
 */
void __stdio_exit_needed(void)
{
	static int registered;

	if (!registered)
	{
		registered = 1;
		atexit(__stdio_exit);
	}
}
