#include <stdlib.h>
#include "heap.h"

void free(void *old_ptr)
{
	__libc_heap_release(old_ptr);
}
