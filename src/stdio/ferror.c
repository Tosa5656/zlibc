#include "../internal/stdio_impl.h"

int ferror(FILE *f)
{
	int ret;

	FLOCK(f);

	ret = !!(f->flags & F_ERR);

	FUNLOCK(f);

	return ret;
}
