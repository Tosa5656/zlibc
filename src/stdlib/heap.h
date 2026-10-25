#ifndef ZLIBC_STDLIB_HEAP_INTERNAL_H
#define ZLIBC_STDLIB_HEAP_INTERNAL_H

#include <stddef.h>

void *__libc_heap_alloc(size_t num_bytes);
void *__libc_heap_alloc_aligned(size_t alignment, size_t num_bytes);
void *__libc_heap_resize(void *old_ptr, size_t num_bytes);
void __libc_heap_release(void *old_ptr);

#endif
