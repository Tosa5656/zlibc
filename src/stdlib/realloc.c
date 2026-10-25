#include <stdlib.h>
#include "heap.h"

void *realloc(void *old_ptr, size_t num_bytes)
{
	return __libc_heap_resize(old_ptr, num_bytes);
}
