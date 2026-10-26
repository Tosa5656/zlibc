#include "../internal/stdio_impl.h"
#include <string.h>

#define MIN(a,b) ((a)<(b) ? (a) : (b))

char *fgets(char *__restrict s, int n, FILE *__restrict f)
{
	char *p = s;
	unsigned char *z;
	size_t k;
	int c;

	FLOCK(f);

	if (n <= 1)
	{
		f->mode |= f->mode-1;
		FUNLOCK(f);

		if (n < 1)
		{
			return 0;
		}

		*s = 0;

		return s;
	}

	n--;

	while (n)
	{
		if (f->rpos != f->rend)
		{
			z = memchr(f->rpos, '\n', f->rend - f->rpos);
			k = z ? (size_t)(z - f->rpos) + 1 : (size_t)(f->rend - f->rpos);
			k = MIN(k, (size_t)n);

			memcpy(p, f->rpos, k);
			f->rpos += k;
			p += k;
			n -= k;

			if (z || !n)
			{
				break;
			}
		}

		if ((c = fgetc(f)) < 0)
		{
			if (p == s || !feof(f))
			{
				s = 0;
			}

			break;
		}

		n--;

		if ((*p++ = c) == '\n')
		{
			break;
		}
	}

	if (s)
	{
		*p = 0;
	}

	FUNLOCK(f);

	return s;
}
