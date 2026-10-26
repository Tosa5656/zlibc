#include "../internal/stdio_impl.h"
#include <stdlib.h>

int fclose(FILE *f)
{
	int r;

	FLOCK(f);

	r = fflush(f);
	r |= f->close(f);

	FUNLOCK(f);
	
	if (f->flags & F_PERM)
	{
		return r;
	}

	{
		FILE **head = __ofl_lock();

		if (f->prev)
		{
			f->prev->next = f->next;
		}

		if (f->next)
		{
			f->next->prev = f->prev;
		}

		if (*head == f)
		{
			*head = f->next;
		}
	}

	free(f->getln_buf);
	free(f);

	return r;
}
