#include <stdlib.h>
#include "heap.h"

void *malloc(size_t num_bytes)
{
	return __libc_heap_alloc(num_bytes);
}
