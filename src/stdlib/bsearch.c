#include <stdlib.h>

void *bsearch(const void *key, const void *base, size_t element_count, size_t element_size, int (*compar)(const void *, const void *))
{
	const unsigned char *elements = base;
	size_t low = 0;
	size_t high = element_count;

	if (key == NULL || base == NULL || element_size == 0)
	{
		return NULL;
	}

	while (low < high)
	{
		size_t middle = low + (high - low) / 2;
		int order = compar(key, elements + middle * element_size);

		if (order == 0)
		{
			return (void *)(elements + middle * element_size);
		}

		if (order > 0)
		{
			low = middle + 1;
		}
		else
		{
			high = middle;
		}
	}

	return NULL;
}
