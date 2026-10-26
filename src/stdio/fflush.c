#include "../internal/stdio_impl.h"

int fflush(FILE *f)
{
	if (!f)
	{
		int r = 0;
		FILE **head;

		r |= fflush(__stdout_used);
		r |= fflush(__stderr_used);

		head = __ofl_lock();

		for (f = *head; f; f = f->next)
		{
			if (f->wpos != f->wbase)
			{
				r |= fflush(f);
			}
		}

		return r;
	}

	FLOCK(f);

	if (f->wpos != f->wbase)
	{
		f->write(f, 0, 0);

		if (!f->wpos)
		{
			FUNLOCK(f);

			return EOF;
		}
	}

	if (f->rpos != f->rend)
	{
		f->seek(f, f->rpos-f->rend, SEEK_CUR);
	}

	f->wpos = f->wbase = f->wend = 0;
	f->rpos = f->rend = 0;

	FUNLOCK(f);

	return 0;
}
