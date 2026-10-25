#include <stdlib.h>
#include <string.h>

#define QSORT_INSERTION_MAX 16

typedef int (*qsort_compare)(const void *, const void *);

static void qsort_swap_bytes(unsigned char *left, unsigned char *right, size_t size)
{
	while (size--)
	{
		unsigned char temporary = *left;

		*left++ = *right;
		*right++ = temporary;
	}
}

static void qsort_insertion(unsigned char *base, size_t count, size_t size, qsort_compare compare)
{
	size_t index;

	for (index = 1; index < count; index++)
	{
		size_t hole = index;

		while (hole > 0 && compare(base + (hole - 1) * size, base + hole * size) > 0)
		{
			qsort_swap_bytes(base + (hole - 1) * size, base + hole * size, size);
			hole--;
		}
	}
}

static void qsort_sift_down(unsigned char *base, size_t count, size_t size,
	size_t root, qsort_compare compare)
{
	for (;;)
	{
		size_t child = root * 2 + 1;

		if (child >= count)
		{
			return;
		}

		if (child + 1 < count && compare(base + child * size, base + (child + 1) * size) < 0)
		{
			child++;
		}

		if (compare(base + root * size, base + child * size) >= 0)
		{
			return;
		}

		qsort_swap_bytes(base + root * size, base + child * size, size);
		root = child;
	}
}

static void qsort_heapsort(unsigned char *base, size_t count, size_t size, qsort_compare compare)
{
	size_t index;

	if (count < 2)
	{
		return;
	}

	for (index = count / 2; index-- > 0;)
	{
		qsort_sift_down(base, count, size, index, compare);
	}

	for (index = count - 1; index > 0; index--)
	{
		qsort_swap_bytes(base, base + index * size, size);
		qsort_sift_down(base, index, size, 0, compare);
	}
}

static void qsort_merge(unsigned char *base, size_t half, size_t count,
	size_t size, qsort_compare compare, unsigned char *scratch)
{
	size_t left = 0;
	size_t right = half;
	size_t out = 0;

	memcpy(scratch, base, half * size);

	while (left < half && right < count)
	{
		if (compare(scratch + left * size, base + right * size) <= 0)
		{
			memcpy(base + out * size, scratch + left * size, size);
			left++;
		}
		else
		{
			memcpy(base + out * size, base + right * size, size);
			right++;
		}

		out++;
	}

	if (left < half)
	{
		memcpy(base + out * size, scratch + left * size, (half - left) * size);
	}
}

static void qsort_recurse(unsigned char *base, size_t count, size_t size, qsort_compare compare)
{
	size_t half;
	unsigned char *scratch;

	if (count <= QSORT_INSERTION_MAX)
	{
		qsort_insertion(base, count, size, compare);

		return;
	}

	half = count / 2;

	qsort_recurse(base, half, size, compare);
	qsort_recurse(base + half * size, count - half, size, compare);

	if (compare(base + (half - 1) * size, base + half * size) <= 0)
	{
		return;
	}

	scratch = malloc(half * size);
	if (scratch != NULL)
	{
		qsort_merge(base, half, count, size, compare, scratch);
		free(scratch);

		return;
	}

	qsort_heapsort(base, count, size, compare);
}

void qsort(void *vbase, size_t count, size_t size, qsort_compare compare)
{
	if (vbase == NULL || count < 2 || size == 0)
	{
		return;
	}

	qsort_recurse((unsigned char *)vbase, count, size, compare);
}
