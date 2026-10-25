#include <stdlib.h>
#include <string.h>
#include "heap.h"

void *calloc(size_t element_count, size_t element_size)
{
	size_t num_bytes;
	unsigned char *memory;

	if (element_count == 0 || element_size == 0)
	{
		return NULL;
	}

	if (element_size > ((size_t)-1) / element_count)
	{
		return NULL;
	}

	num_bytes = element_count * element_size;

	memory = __libc_heap_alloc(num_bytes);
	if (memory != NULL)
	{
		memset(memory, 0, num_bytes);
	}

	return memory;
}
