#include <stdlib.h>
#include "heap.h"

void *aligned_alloc(size_t alignment, size_t num_bytes)
{
	return __libc_heap_alloc_aligned(alignment, num_bytes);
}
