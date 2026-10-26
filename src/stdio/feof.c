#include "../internal/stdio_impl.h"

int feof(FILE *f)
{
	int ret;

	FLOCK(f);

	ret = !!(f->flags & F_EOF);

	FUNLOCK(f);

	return ret;
}
