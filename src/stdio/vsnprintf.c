#include "../internal/stdio_impl.h"
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

struct sn_cookie
{
	char *s;
	size_t n;
};

#define MIN(a, b) ((a) < (b) ? (a) : (b))

static size_t sn_write(FILE *f, const unsigned char *s, size_t l)
{
	struct sn_cookie *c = f->cookie;
	size_t k = MIN(c->n, (size_t)(f->wpos - f->wbase));

	if (k)
	{
		memcpy(c->s, f->wbase, k);
		c->s += k;
		c->n -= k;
	}

	k = MIN(c->n, l);

	if (k)
	{
		memcpy(c->s, s, k);
		c->s += k;
		c->n -= k;
	}

	*c->s = 0;
	f->wpos = f->wbase = f->buf;

	return l;
}

int vsnprintf(char *__restrict s, size_t n, const char *__restrict fmt, va_list ap)
{
	unsigned char buf[1];
	char dummy[1];
	struct sn_cookie c = { .s = n ? s : dummy, .n = n ? n-1 : 0 };
	FILE f =
	{
		.lbf = EOF,
		.write = sn_write,
		.lock = -1,
		.buf = buf,
		.cookie = &c,
	};

	*c.s = 0;

	return vfprintf(&f, fmt, ap);
}
